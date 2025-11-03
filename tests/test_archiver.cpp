#include "archiver.hpp"
#include <cassert>
#include <fstream>
#include <iostream>

using namespace csi::archive;

int main() {
    // prepare sample input
    std::ofstream out("input.txt");
    out << "alpha\n";
    out << "beta gamma\n";
    out << "delta epsilon zeta\n";
    out.close();

    DataArchiver arch("input.txt");
    assert(arch.load_text() && "load_text failed");

    bool saved = arch.save_binary("data.bin");
    assert(saved && "save_binary failed");

#if defined(ENABLE_RESTORE)
    bool restored = arch.restore_binary("data.bin");
    assert(restored && "restore_binary failed");

    std::cout << "Restored content:\n";
    arch.print_restored();
#endif

    std::cout << "✅ All tests passed.\n";
}
