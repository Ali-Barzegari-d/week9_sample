#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace csi::snapshot {

class Snapshot {
public:
    explicit Snapshot(std::string path);

    // Saves the given data vector to a binary file
    template <typename T>
    void save(const std::vector<T>& data) {
        std::ofstream out(filepath, std::ios::binary | std::ios::trunc);
        if (!out.is_open()) {
            throw std::runtime_error("Cannot open file for writing");
        }

#if defined(SNAPSHOT_LOG)
        std::cout << "[LOG] Saving snapshot with " << data.size() << " elements.\n";
#endif

        // Write element count
        size_t count = data.size();
        out.write(reinterpret_cast<const char*>(&count), sizeof(size_t));

        // Write raw data
        if (!data.empty()) {
            out.write(reinterpret_cast<const char*>(data.data()), sizeof(T) * count);
        }

        if (!out.good()) {
            throw std::runtime_error("Error occurred during writing");
        }

#if defined(SNAPSHOT_LOG)
        std::cout << "[LOG] Snapshot successfully saved.\n";
#endif
    }

    // Loads and returns the stored vector from the binary file
    template <typename T>
    std::vector<T> load() {
        std::ifstream in(filepath, std::ios::binary);
        if (!in.is_open()) {
            throw std::runtime_error("Cannot open file for reading");
        }

#if defined(SNAPSHOT_LOG)
        std::cout << "[LOG] Loading snapshot from file.\n";
#endif

        // Read element count
        size_t count = 0;
        in.read(reinterpret_cast<char*>(&count), sizeof(size_t));

        std::vector<T> result(count);
        if (count > 0) {
            in.read(reinterpret_cast<char*>(result.data()), sizeof(T) * count);
        }

        if (!in.good() && !in.eof()) {
            throw std::runtime_error("Error occurred during reading");
        }

#if defined(SNAPSHOT_LOG)
        std::cout << "[LOG] Loaded " << count << " elements successfully.\n";
#endif

        return result;
    }

private:
    std::string filepath;
};

} // namespace csi::snapshot
