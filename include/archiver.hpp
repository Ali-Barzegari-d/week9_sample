#pragma once
#include <string>
#include <vector>

namespace csi::archive {

class DataArchiver {
public:
    explicit DataArchiver(std::string input_path);

    // Loads data (text lines) from the input file
    bool load_text();

    // Saves loaded data to a binary file
    bool save_binary(const std::string& out_path) const;

#if defined(ENABLE_RESTORE)
    // Restores data from a binary file
    bool restore_binary(const std::string& bin_path);
    // Prints restored data to console
    void print_restored() const;
#endif

private:
    std::string input_file;
    std::vector<std::string> lines;

#if defined(ENABLE_RESTORE)
    std::vector<std::string> restored;
#endif
};

} // namespace csi::archive
