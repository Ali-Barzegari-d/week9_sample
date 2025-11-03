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
        // TODO:
        // Open the file in binary write mode (trunc).
        // Write the number of elements first (size_t).
        // Then write all elements as raw bytes.
        // If file cannot be opened, throw std::runtime_error("Cannot open file for writing").
        // Use RAII (no manual close).
        // If SNAPSHOT_LOG is defined, print debug messages.
    }

    // Loads and returns the stored vector from the binary file
    template <typename T>
    std::vector<T> load() {
        // TODO:
        // Open the file in binary read mode.
        // Read the number of elements (size_t).
        // Read that many items into a vector and return it.
        // If file cannot be opened, throw std::runtime_error("Cannot open file for reading").
        // If SNAPSHOT_LOG is defined, print debug messages.
        return {}; // placeholder
    }

private:
    std::string filepath;
};

} // namespace csi::snapshot
