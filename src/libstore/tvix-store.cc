#include "archive.hh"
#include "hash.hh"
#include "callback.hh"
#include "logging.hh"
#include "path-info.hh"
#include "pathinfo.pb.h"
#include "rpc_pathinfo.pb.h"
#include "tvix-store.hh"
#include "url.hh"
#include "util.hh"
#include <cstring>
#include <iterator>
#include <memory>
#include <regex>

namespace nix {

TvixStore::TvixStore(const Params & params)
    : StoreConfig(params)
    , LocalFSStoreConfig(params)
    , TvixStoreConfig(params)
    , Store(params)
    , LocalFSStore(params)
    , stub_(tvix::store::v1::PathInfoService::NewStub(grpc::CreateChannel("localhost:8000", grpc::InsecureChannelCredentials())))
{
}

TvixStore::TvixStore(std::string scheme, std::string path, const Params & params)
    : TvixStore(params)
{}

void TvixStore::narFromPath(const StorePath & path, Sink & sink)
{
    debug("narFromPath");
    unsupported("narFromPath");
}

void TvixStore::queryPathInfoUncached(
    const StorePath & path, Callback<std::shared_ptr<const ValidPathInfo>> callback) noexcept
{
    debug("queryPathInfoUncached");
    // TODO: async
    auto callbackPtr = std::make_shared<decltype(callback)>(std::move(callback));

    grpc::ClientContext context;

    try {
        tvix::store::v1::GetPathInfoRequest req;
        auto hash = Hash::parseAny(path.hashPart(), HashType::htSHA1);
        req.set_by_output_hash(hash.hash, hash.hashSize);

        tvix::store::v1::PathInfo res;
        auto status = this->stub_->Get(&context, req, &res);
        if (!status.ok()) {
            return (*callbackPtr)({});
        }

        auto narHash = Hash(HashType::htSHA256);
        if (narHash.hashSize != res.narinfo().nar_sha256().size()) {
            throw nix::Error("unexpected nar hash size");
        }
        std::memcpy(narHash.hash, res.narinfo().nar_sha256().c_str(), res.narinfo().nar_sha256().size());
        auto validPathInfo = std::make_shared<ValidPathInfo>(path, narHash);

        return (*callbackPtr)(std::move(validPathInfo));
    } catch (...) {
        return callbackPtr->rethrow();
    }
}

// Unimplemented methods
std::optional<StorePath> TvixStore::queryPathFromHashPart(const std::string & hashPart)
{
    debug("queryPathInfoUncached");
    // TODO: async

    grpc::ClientContext context;

    tvix::store::v1::GetPathInfoRequest req;
    auto hash = Hash::parseAny(hashPart, HashType::htSHA1);
    req.set_by_output_hash(hash.hash, hash.hashSize);

    tvix::store::v1::PathInfo res;
    auto status = this->stub_->Get(&context, req, &res);
    if (!status.ok()) {
        return {};
    }

    if (res.node().has_file()) {
        return StorePath(std::string_view(res.node().file().name()));
    }
    if (res.node().has_directory()) {
        return StorePath(std::string_view(res.node().directory().name()));
    }
    if (res.node().has_symlink()) {
        return StorePath(std::string_view(res.node().symlink().name()));
    }

    return {};
}
void TvixStore::addToStore(const ValidPathInfo & info, Source & source,
                                  RepairFlag repair, CheckSigsFlag checkSigs)
{
    unsupported("addToStore");
}
StorePath TvixStore::addTextToStore(
    std::string_view name,
    std::string_view s,
    const StorePathSet & references,
    RepairFlag repair)
{ unsupported("addTextToStore"); }
void TvixStore::queryRealisationUncached(const DrvOutput & drvOutput,
    Callback<std::shared_ptr<const Realisation>> callback) noexcept
{
    debug("queryRealisationUncached");
    unsupported("queryRealisationUncached");
}
std::optional<TrustedFlag> TvixStore::isTrustedClient()
{
    debug("isTrustedClient");
    unsupported("isTrustedClient");
}
void TvixStore::addIndirectRoot(const Path & path)
{ unsupported("addIndirectRoot"); }
Roots TvixStore::findRoots(bool censor)
{ unsupported("findRoots"); }
void TvixStore::collectGarbage(const GCOptions & options, GCResults & results)
{ unsupported("collectGarbage"); }
void TvixStore::addBuildLog(const StorePath & path, std::string_view log)
{ unsupported("addBuildLog"); }
Path TvixStore::addPermRoot(const StorePath & storePath, const Path & gcRoot)
{ unsupported("addPermRoot"); }

static RegisterStoreImplementation<TvixStore, TvixStoreConfig> regTvixStore;
}
