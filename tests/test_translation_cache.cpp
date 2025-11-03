#include "translation_cache.hpp"
#include <cassert>
#include <iostream>
#include <fstream>

using namespace csi::translate;

int main() {
    // Prepare a small translation cache
    TranslationCache tc("cache.txt");
    tc.load();

    std::string t1 = tc.translate("hello");
    std::string t2 = tc.translate("world");
    std::string t3 = tc.translate("hello"); // should be cached

    assert(!t1.empty());
    assert(t3 == t1 && "Expected cached translation");

#if defined(READONLY_CACHE)
    std::string t4 = tc.translate("newword");
    assert(t4 == "[MISSING]" && "Readonly cache shouldn't add new entries");
#endif

    tc.save();

    // Re-load to ensure persistence
    TranslationCache tc2("cache.txt");
    tc2.load();
    assert(tc2.translate("world") == t2);

    std::cout << "✅ All tests passed.\n";
}
