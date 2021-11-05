#pragma once

#include "symbol-table.hh"

#if HAVE_BOEHMGC
#include <gc/gc_allocator.h>
#endif

namespace nix {


typedef enum {
    tInt = 1,
    tBool,
    tString,
    tPath,
    tNull,
    tAttrs,
    tList1,
    tList2,
    tListN,
    tThunk,
    tApp,
    tPartialApp,
    tLambda,
    tBlackhole,
    tPrimOp,
    tPrimOpApp,
    tExternal,
    tFloat
} InternalType;

// This type abstracts over all actual value types in the language,
// grouping together implementation details like tList*, different function
// types, and types in non-normal form (so thunks and co.)
typedef enum {
    nThunk,
    nInt,
    nFloat,
    nBool,
    nString,
    nPath,
    nNull,
    nAttrs,
    nList,
    nFunction,
    nExternal
} ValueType;

class Bindings;
struct Env;
struct Expr;
struct ExprLambda;
struct PrimOp;
class Symbol;
struct Pos;
class EvalState;
class XMLWriter;
class JSONPlaceholder;


typedef int64_t NixInt;
typedef double NixFloat;

/* External values must descend from ExternalValueBase, so that
 * type-agnostic nix functions (e.g. showType) can be implemented
 */
class ExternalValueBase
{
    friend std::ostream & operator << (std::ostream & str, const ExternalValueBase & v);
    protected:
    /* Print out the value */
    virtual std::ostream & print(std::ostream & str) const = 0;

    public:
    /* Return a simple string describing the type */
    virtual string showType() const = 0;

    /* Return a string to be used in builtins.typeOf */
    virtual string typeOf() const = 0;

    /* Coerce the value to a string. Defaults to uncoercable, i.e. throws an
     * error
     */
    virtual string coerceToString(const Pos & pos, PathSet & context, bool copyMore, bool copyToStore) const;

    /* Compare to another value of the same type. Defaults to uncomparable,
     * i.e. always false.
     */
    virtual bool operator==(const ExternalValueBase & b) const;

    /* Print the value as JSON. Defaults to unconvertable, i.e. throws an error */
    virtual void printValueAsJSON(EvalState & state, bool strict,
        JSONPlaceholder & out, PathSet & context) const;

    /* Print the value as XML. Defaults to unevaluated */
    virtual void printValueAsXML(EvalState & state, bool strict, bool location,
        XMLWriter & doc, PathSet & context, PathSet & drvsSeen) const;

    virtual ~ExternalValueBase()
    {
    };
};

std::ostream & operator << (std::ostream & str, const ExternalValueBase & v);


struct Value
{
private:
    InternalType internalType;

friend std::string showType(const Value & v);
friend void printValue(std::ostream & str, std::set<const Value *> & active, const Value & v);

public:

    // Functions needed to distinguish the type
    // These should be removed eventually, by putting the functionality that's
    // needed by callers into methods of this type

    // type() == nThunk
    inline bool isThunk() const { return internalType == tThunk; };
    inline bool isApp() const { return internalType == tApp; };
    inline bool isBlackhole() const { return internalType == tBlackhole; };

    // type() == nFunction
    inline bool isLambda() const { return internalType == tLambda; };
    inline bool isPartialApp() const { return internalType == tPartialApp; };
    inline bool isPrimOp() const { return internalType == tPrimOp; };
    inline bool isPrimOpApp() const { return internalType == tPrimOpApp; };

    union
    {
        NixInt integer;
        bool boolean;

        /* Strings in the evaluator carry a so-called `context' which
           is a list of strings representing store paths.  This is to
           allow users to write things like

             "--with-freetype2-library=" + freetype + "/lib"

           where `freetype' is a derivation (or a source to be copied
           to the store).  If we just concatenated the strings without
           keeping track of the referenced store paths, then if the
           string is used as a derivation attribute, the derivation
           will not have the correct dependencies in its inputDrvs and
           inputSrcs.

           The semantics of the context is as follows: when a string
           with context C is used as a derivation attribute, then the
           derivations in C will be added to the inputDrvs of the
           derivation, and the other store paths in C will be added to
           the inputSrcs of the derivations.

           For canonicity, the store paths should be in sorted order. */
        struct {
            const char * s;
            const char * * context; // must be in sorted order
        } string;

        const char * path;
        Bindings * attrs;
        struct {
            size_t size;
            Value * * elems;
        } bigList;
        Value * smallList[2];
        struct {
            Env * env;
            Expr * expr;
        } thunk;
        struct {
            Value * left, * right;
        } app;
        struct {
            Env * env;
            ExprLambda * fun;
        } lambda;
        PrimOp * primOp;
        struct {
            Value * left, * right;
        } primOpApp;
        ExternalValueBase * external;
        NixFloat fpoint;
    };

    // Returns the normal type of a Value. This only returns nThunk if the
    // Value hasn't been forceValue'd
    inline ValueType type() const
    {
        switch (internalType) {
            case tInt: return nInt;
            case tBool: return nBool;
            case tString: return nString;
            case tPath: return nPath;
            case tNull: return nNull;
            case tAttrs: return nAttrs;
            case tList1: case tList2: case tListN: return nList;
            case tLambda: case tPartialApp: case tPrimOp: case tPrimOpApp: return nFunction;
            case tExternal: return nExternal;
            case tFloat: return nFloat;
            case tThunk: case tApp: case tBlackhole: return nThunk;
        }
        abort();
    }

    /* After overwriting an app node, be sure to clear pointers in the
       Value to ensure that the target isn't kept alive unnecessarily. */
    inline void clearValue()
    {
        app.left = app.right = 0;
    }

    inline void mkInt(NixInt n)
    {
        clearValue();
        internalType = tInt;
        integer = n;
    }

    inline void mkBool(bool b)
    {
        clearValue();
        internalType = tBool;
        boolean = b;
    }

    inline void mkString(const char * s, const char * * context = 0)
    {
        internalType = tString;
        string.s = s;
        string.context = context;
    }

    inline void mkPath(const char * s)
    {
        clearValue();
        internalType = tPath;
        path = s;
    }

    inline void mkNull()
    {
        clearValue();
        internalType = tNull;
    }

    inline void mkAttrs(Bindings * a)
    {
        clearValue();
        internalType = tAttrs;
        attrs = a;
    }

    inline void mkList(size_t size)
    {
        clearValue();
        if (size == 1)
            internalType = tList1;
        else if (size == 2)
            internalType = tList2;
        else {
            internalType = tListN;
            bigList.size = size;
        }
    }

    inline void mkThunk(Env * e, Expr * ex)
    {
        internalType = tThunk;
        thunk.env = e;
        thunk.expr = ex;
    }

    inline void mkApp(Value * l, Value * r)
    {
        internalType = tApp;
        app.left = l;
        app.right = r;
    }

    inline void mkLambda(Env * e, ExprLambda * f)
    {
        internalType = tLambda;
        lambda.env = e;
        lambda.fun = f;
    }

    inline void mkBlackhole()
    {
        internalType = tBlackhole;
        // Value will be overridden anyways
    }

    inline void mkPrimOp(PrimOp * p)
    {
        clearValue();
        internalType = tPrimOp;
        primOp = p;
    }


    inline void mkPrimOpApp(Value * l, Value * r)
    {
        internalType = tPrimOpApp;
        app.left = l;
        app.right = r;
    }

    inline void mkPartialApp(Value * l, Value * r)
    {
        internalType = tPartialApp;
        app.left = l;
        app.right = r;
    }

    inline void mkExternal(ExternalValueBase * e)
    {
        clearValue();
        internalType = tExternal;
        external = e;
    }

    inline void mkFloat(NixFloat n)
    {
        clearValue();
        internalType = tFloat;
        fpoint = n;
    }

    bool isList() const
    {
        return internalType == tList1 || internalType == tList2 || internalType == tListN;
    }

    Value * * listElems()
    {
        return internalType == tList1 || internalType == tList2 ? smallList : bigList.elems;
    }

    const Value * const * listElems() const
    {
        return internalType == tList1 || internalType == tList2 ? smallList : bigList.elems;
    }

    size_t listSize() const
    {
        return internalType == tList1 ? 1 : internalType == tList2 ? 2 : bigList.size;
    }

    Pos determinePos(const Pos &pos) const;

    /* Check whether forcing this value requires a trivial amount of
       computation. In particular, function applications are
       non-trivial. */
    bool isTrivial() const;

    std::vector<std::pair<Path, std::string>> getContext();
};



// TODO: Remove these static functions, replace call sites with v.mk* instead
static inline void mkInt(Value & v, NixInt n)
{
    v.mkInt(n);
}

static inline void mkFloat(Value & v, NixFloat n)
{
    v.mkFloat(n);
}

static inline void mkBool(Value & v, bool b)
{
    v.mkBool(b);
}

static inline void mkNull(Value & v)
{
    v.mkNull();
}

static inline void mkApp(Value & v, Value & left, Value & right)
{
    v.mkApp(&left, &right);
}

static inline void mkString(Value & v, const Symbol & s)
{
    v.mkString(((const string &) s).c_str());
}


void mkString(Value & v, const char * s);


void mkPath(Value & v, const char * s);


#if HAVE_BOEHMGC
typedef std::vector<Value *, traceable_allocator<Value *> > ValueVector;
typedef std::map<Symbol, Value *, std::less<Symbol>, traceable_allocator<std::pair<const Symbol, Value *> > > ValueMap;
#else
typedef std::vector<Value *> ValueVector;
typedef std::map<Symbol, Value *> ValueMap;
#endif


/* A value allocated in traceable memory. */
typedef std::shared_ptr<Value *> RootValue;

RootValue allocRootValue(Value * v);

}
