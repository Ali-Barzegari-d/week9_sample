#pragma once
#include <string>
#include <unordered_map>

namespace csi::translate {

class TranslationCache {
public:
    explicit TranslationCache(std::string cache_file);

    // Loads existing cache from file
    bool load();

    // Saves current cache to file
    bool save() const;

    // Returns translated string, possibly using cache
    std::string translate(const std::string& input);

private:
    std::string filepath;
    std::unordered_map<std::string, std::string> cache;

    // Generates a fake translation (used when no cached translation exists)
    std::string fake_translate(const std::string& input) const;
};

} // namespace csi::translate
