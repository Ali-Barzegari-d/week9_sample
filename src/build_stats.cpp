#include "build_stats.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <numeric>
#include <filesystem>
#include <algorithm>

using namespace std;
using namespace csi::build;

// Constructor
BuildStats::BuildStats(const std::string& log_path)
    : m_path(log_path) {
    // Ensure log file exists (create if missing)
    std::ofstream file(m_path, std::ios::app);
    // file closes automatically via RAII
}

// Add a new record
void BuildStats::add_record(const ModuleStat& m) {
    m_records.push_back(m);

#ifdef BUILD_DEBUG
    std::cout << "[BuildDebug] module=" << m.name
              << ", time=" << std::fixed << std::setprecision(2)
              << m.compile_time << "s, success=" << std::boolalpha
              << m.success << "\n";
#endif
}

// Compute average compile time for successful modules
double BuildStats::avg_success_time() const {
    double sum = 0.0;
    int count = 0;
    for (const auto& r : m_records) {
        if (r.success) {
            sum += r.compile_time;
            count++;
        }
    }
    return (count == 0) ? 0.0 : (sum / count);
}

// Compute success rate percentage (0–100)
double BuildStats::success_rate() const {
    if (m_records.empty()) return 0.0;
    int ok = 0;
    for (const auto& r : m_records)
        if (r.success) ok++;
    return (100.0 * ok) / m_records.size();
}

// Save formatted report to file
void BuildStats::save_report() const {
    std::ofstream out(m_path, std::ios::trunc);
    if (!out) return;

    double rate = success_rate();
    double avg = avg_success_time();

    out << "--- Build Report ---\n";
    out << "total modules: " << m_records.size() << "\n";
    out << "success: " << std::count_if(m_records.begin(), m_records.end(),
                                       [](auto& m) { return m.success; })
        << " (" << std::fixed << std::setprecision(2) << rate << "%)\n";
    out << "avg success time: " << std::fixed << std::setprecision(2)
        << avg << "s\n";
    out << "modules:\n";

    for (const auto& r : m_records) {
        out << "  " << std::left << std::setw(10) << r.name << " -> "
            << std::fixed << std::setprecision(2) << r.compile_time << "s "
            << (r.success ? "[OK]" : "[FAIL]") << "\n";
    }
}

// Clear memory and truncate log file
void BuildStats::clear() {
    m_records.clear();
    std::ofstream out(m_path, std::ios::trunc);
    // File automatically truncated
}

// Return compact string summary
std::string BuildStats::summary() const {
    std::ostringstream ss;
    ss << m_records.size() << " modules, "
       << std::fixed << std::setprecision(1)
       << success_rate() << "% success, avg="
       << std::setprecision(2) << avg_success_time() << "s";
    return ss.str();
}
