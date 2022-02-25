#include "store-api.hh"
#include "callback.hh"
#include "nar-info.hh"
#include <iostream>

namespace nix {

struct CachefsStoreConfig : virtual StoreConfig {
    using StoreConfig::StoreConfig;

    const std::string name() override { return "Cachefs Store 1234"; }
};

struct CachefsStore : public virtual CachefsStoreConfig, public virtual Store
{
    std::string rootPath;

    CachefsStore(const std::string scheme, const std::string & path, const Params & params)
        : StoreConfig(params)
        , CachefsStoreConfig(params)
        , Store(params)
        , rootPath(path)
    { }

    bool isValidPathUncached(const StorePath &path) override
    {
        // TODO(cbrewster): Actually check this...
        // this a lie
        return true;
    }

    string getUri() override
    {
        return *uriSchemes().begin();
    }

    StorePathSet querySubstitutablePaths(const StorePathSet & paths) override
    { 
        std::cerr << "querySubstitutablePaths: " << paths.begin()->hashPart() << std::endl;
        return {}; 
    };

    StorePathSet queryValidPaths(const StorePathSet & paths,
        SubstituteFlag maybeSubstitute = NoSubstitute) override {
        std::cerr << "queryPathInfoUncached: " << paths.begin()->hashPart() << std::endl;
        unsupported("qeuryValidPaths");
    }

    void queryPathInfoUncached(const StorePath & path,
        Callback<std::shared_ptr<const ValidPathInfo>> callback) noexcept override
    {
        try {
            auto narinfo_path = rootPath + "/" + std::string{path.hashPart()} + ".narinfo";
            auto narinfo_str = nix::readFile(narinfo_path);
            callback((std::shared_ptr<ValidPathInfo>)
                    std::make_shared<NarInfo>(*this, narinfo_str, narinfo_path));
            std::cerr << "queryRealisationUncached: " << path.hashPart() << std::endl;
        } catch (...) {
            callback(nullptr); 
        }
    }

    static std::set<std::string> uriSchemes() {
        return {"cachefs"};
    }

    std::optional<StorePath> queryPathFromHashPart(const std::string & hashPart) override
    { 
        std::cerr << "queryPathFromHashPart: " << hashPart << std::endl;
        unsupported("queryPathFromHashPart"); 
    }

    void addToStore(const ValidPathInfo & info, Source & source,
        RepairFlag repair, CheckSigsFlag checkSigs) override
    { unsupported("addToStore"); }

    StorePath addTextToStore(const string & name, const string & s,
        const StorePathSet & references, RepairFlag repair) override
    { unsupported("addTextToStore"); }

    void narFromPath(const StorePath & path, Sink & sink) override
    { 
        std::cerr << "narFromPath: " << path.hashPart() << std::endl;
        auto narinfo_path = rootPath + "/" + std::string{path.hashPart()} + ".narinfo";
        auto narinfo_str = nix::readFile(narinfo_path);
        sink(narinfo_str);
    }

    void queryRealisationUncached(const DrvOutput & drv,
        Callback<std::shared_ptr<const Realisation>> callback) noexcept override
    { 
        callback(nullptr);
    }
};

static RegisterStoreImplementation<CachefsStore, CachefsStoreConfig> regCachefsStore;

}
