#include "snapshot.hpp"
#include <cassert>
#include <iostream>

using namespace csi::snapshot;

int main() {
    Snapshot s("state.bin");

    std::vector<int> data = {10, 20, 30, 40, 50};
    s.save(data);

    auto loaded = s.load<int>();
    assert(loaded == data && "Loaded data must match original");

#if defined(SNAPSHOT_LOG)
    std::cout << "Snapshot saved and loaded successfully.\n";
#endif

    std::cout << "✅ All tests passed.\n";
}
