#include "build_stats.hpp"
#include <cassert>
#include <iostream>
#include <fstream>

using namespace csi::build;

int main() {
    BuildStats stats("build_log.txt");
    stats.clear();

    stats.add_record({"core.cpp", 1.23, true});
    stats.add_record({"util.cpp", 1.47, true});
    stats.add_record({"net.cpp", 2.01, false});

    double avg = stats.avg_success_time();
    double rate = stats.success_rate();
    std::string summary = stats.summary();

    assert(avg > 1.3 && avg < 1.4);
    assert(rate > 60.0 && rate < 70.0);
    assert(summary.find("3 modules") != std::string::npos);

    stats.save_report();
    std::ifstream f("build_log.txt");
    std::string content((std::istreambuf_iterator<char>(f)), {});
    assert(content.find("Build Report") != std::string::npos);
    assert(content.find("core.cpp") != std::string::npos);

    std::cout << "✅ BuildStats tests passed.\n";
    return 0;
}
