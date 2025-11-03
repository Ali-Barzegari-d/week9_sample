#include "archiver.hpp"
#include <fstream>
#include <iostream>

namespace csi::archive {

DataArchiver::DataArchiver(std::string input_path)
    : input_file(std::move(input_path)) {}

bool DataArchiver::load_text() {
    std::ifstream in(input_file);
    if (!in.is_open()) {
        std::cerr << "❌ Failed to open input file: " << input_file << "\n";
        return false;
    }

    lines.clear();
    std::string line;
    while (std::getline(in, line)) {
        lines.push_back(line);
    }

    if (lines.empty()) {
        std::cerr << "⚠️ No lines read from file.\n";
        return false;
    }

    return true;
}

bool DataArchiver::save_binary(const std::string& out_path) const {
    std::ofstream out(out_path, std::ios::binary);
    if (!out.is_open()) {
        std::cerr << "❌ Failed to open output binary file: " << out_path << "\n";
        return false;
    }

    // Write total number of lines
    size_t num_lines = lines.size();
    out.write(reinterpret_cast<const char*>(&num_lines), sizeof(num_lines));

    for (const auto& line : lines) {
        size_t len = line.size();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(line.data(), static_cast<std::streamsize>(len));
    }

    return true;
}

#if defined(ENABLE_RESTORE)
bool DataArchiver::restore_binary(const std::string& bin_path) {
    std::ifstream in(bin_path, std::ios::binary);
    if (!in.is_open()) {
        std::cerr << "❌ Failed to open binary file: " << bin_path << "\n";
        return false;
    }

    restored.clear();

    size_t num_lines{};
    in.read(reinterpret_cast<char*>(&num_lines), sizeof(num_lines));
    if (!in) return false;

    for (size_t i = 0; i < num_lines; ++i) {
        size_t len{};
        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        if (!in) return false;

        std::string line(len, '\0');
        in.read(line.data(), static_cast<std::streamsize>(len));
        if (!in) return false;

        restored.push_back(std::move(line));
    }

    return true;
}

void DataArchiver::print_restored() const {
    for (const auto& line : restored) {
        std::cout << line << "\n";
    }
}
#endif

} // namespace csi::archive
