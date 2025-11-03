#include "translation_cache.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

namespace csi::translate {

TranslationCache::TranslationCache(std::string cache_file)
    : filepath(std::move(cache_file)) {}

bool TranslationCache::load() {
#if defined(CLEAR_ON_START)
    std::ofstream clear(filepath, std::ios::trunc); // clear the cache
    clear.close();
#endif

    std::ifstream in(filepath);
    if (!in.is_open()) return false;

    std::string key, value;
    cache.clear();

    while (std::getline(in, key) && std::getline(in, value)) {
        cache[key] = value;
    }
    return true;
}

bool TranslationCache::save() const {
#if defined(READONLY_CACHE)
    std::cerr << "⚠️ READONLY_CACHE defined — skipping save.\n";
    return false;
#endif

    std::ofstream out(filepath, std::ios::trunc);
    if (!out.is_open()) return false;

    for (const auto& [k, v] : cache) {
        out << k << "\n" << v << "\n";
    }
    return true;
}

std::string TranslationCache::fake_translate(const std::string& input) const {
    // Simple mock translation: reverse + uppercase
    std::string result(input.rbegin(), input.rend());
    for (auto& ch : result) ch = std::toupper(static_cast<unsigned char>(ch));
    return result;
}

std::string TranslationCache::translate(const std::string& input) {
    auto it = cache.find(input);
    if (it != cache.end()) {
        return it->second;
    }

#if defined(READONLY_CACHE)
    std::cerr << "🔒 Cache is read-only, no new translations allowed.\n";
    return "[MISSING]";
#endif

    std::string translated = fake_translate(input);
    cache[input] = translated;
    save();
    return translated;
}

} // namespace csi::translate
