#include "archiver.hpp"
#include <fstream>
#include <iostream>
#include <string>

namespace csi::archive {

DataArchiver::DataArchiver(std::string input_path)
    : input_file(std::move(input_path)) {}

bool DataArchiver::load_text() {
    // TODO: open input file as std::ifstream (text mode)
    // if fail → return false
    // read all lines and store them in `lines` vector
    // return true if at least one line was read
}

bool DataArchiver::save_binary(const std::string& out_path) const {
    // TODO: open std::ofstream in binary mode
    // write number of lines (size_t)
    // for each line:
    //   - write line length (size_t)
    //   - then write the actual characters
    // return true on success
}

#if defined(ENABLE_RESTORE)
bool DataArchiver::restore_binary(const std::string& bin_path) {
    // TODO: open std::ifstream in binary mode
    // clear `restored`
    // read number of lines
    // for each line:
    //   - read line length
    //   - read characters into string
    // push back to `restored`
    // return true if read successfully
}

void DataArchiver::print_restored() const {
    // TODO: print all restored lines to std::cout, one per line
}
#endif

} // namespace csi::archive
