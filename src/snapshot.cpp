#include "snapshot.hpp"

namespace csi::snapshot {

Snapshot::Snapshot(std::string path)
    : filepath(std::move(path)) {}

} // namespace csi::snapshot
