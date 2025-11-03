#include "plugin_loader.hpp"
#include <cassert>
#include <iostream>
#include <vector>

using namespace csi::plugin;

int main() {
    // Assume the student has compiled mathlib.cpp as a shared library:
    // g++ -shared -fPIC mathlib.cpp -o libmath.so
    PluginLoader loader("./libmath.so");

    assert(loader.is_loaded());
    std::cout << "Library version: " << loader.get_version() << "\n";

    double res1 = loader.call_add(2, 3);
    double res2 = loader.call_mul(6, 7);
    std::vector<double> arr = {1, 2, 3, 4};
    double res3 = loader.call_mean(arr.data(), arr.size());

    assert(res1 == 5);
    assert(res2 == 42);
    assert(res3 > 2.4 && res3 < 2.6);

    std::cout << "✅ All plugin tests passed!\n";
    return 0;
}
