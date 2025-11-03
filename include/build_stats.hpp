#ifndef BUILD_STATS_HPP
#define BUILD_STATS_HPP

#include <string>
#include <vector>
#include <fstream>
#include <chrono>

namespace csi::build {

// Represents a single module build record
struct ModuleStat {
    std::string name;
    double compile_time; // seconds
    bool success;
};

// Collects and reports build statistics
class BuildStats {
public:
    explicit BuildStats(const std::string& log_path);

    void add_record(const ModuleStat& m);      // add new record
    double avg_success_time() const;           // average time of successful builds
    double success_rate() const;               // percentage of successful builds
    void save_report() const;                  // write formatted report to file
    void clear();                              // clear all data and truncate file
    std::string summary() const;               // compact string summary

private:
    std::string m_path;
    std::vector<ModuleStat> m_records;
};

} // namespace csi::build

// If BUILD_DEBUG macro is defined, every added record
// must also be printed to std::cout for live build tracking.
#endif
