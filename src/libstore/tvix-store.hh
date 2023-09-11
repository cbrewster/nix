#include "local-store.hh"
#include "rpc_pathinfo.grpc.pb.h"
#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>

namespace nix {

/**
 * Configuration for `TvixStore`.
 */
struct TvixStoreConfig : virtual LocalFSStoreConfig
{
    TvixStoreConfig(const StringMap & params)
        : StoreConfig(params)
        , LocalFSStoreConfig(params)
    { }

    const std::string name() override { return "Experimental Local Cache Store"; }

    std::string doc() override
    {
        return
          ""
          // FIXME write docs
          //#include "tvix-store.md"
          ;
    }

};

/**
 * Variation of local store that uses a using overlayfs for the store dir.
 */
class TvixStore : public virtual TvixStoreConfig, public virtual LocalFSStore
{

public:
    TvixStore(const Params & params);

    TvixStore(std::string scheme, std::string path, const Params & params);

    static std::set<std::string> uriSchemes()
    { return { "tvix" }; }

    std::string getUri() override
    {
        return "tvix";
    }

private:
    std::unique_ptr<tvix::store::v1::PathInfoService::Stub> stub_;

    // Overridden methods…

    void narFromPath(const StorePath & path, Sink & sink) override;

    void queryPathInfoUncached(const StorePath & path,
        Callback<std::shared_ptr<const ValidPathInfo>> callback) noexcept override;

    std::optional<StorePath> queryPathFromHashPart(const std::string & hashPart);

    void addToStore(const ValidPathInfo & info, Source & source,
                                     RepairFlag repair, CheckSigsFlag checkSigs);

    StorePath addTextToStore(
        std::string_view name,
        std::string_view s,
        const StorePathSet & references,
        RepairFlag repair);

    void queryRealisationUncached(const DrvOutput & drvOutput,
                                  Callback<std::shared_ptr<const Realisation>> callback) noexcept;

    std::optional<TrustedFlag> isTrustedClient();
    void addIndirectRoot(const Path & path);
    Roots findRoots(bool censor);
    void collectGarbage(const GCOptions & options, GCResults & results);
    void addBuildLog(const StorePath & path, std::string_view log);
    Path addPermRoot(const StorePath & storePath, const Path & gcRoot);

};

}
