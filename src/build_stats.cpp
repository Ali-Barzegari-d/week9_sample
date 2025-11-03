#include "build_stats.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <numeric>
#include <filesystem>
#include <algorithm>

// TODO: constructor
// - Store log file path.
// - Ensure the file exists (create it if missing).

// TODO: add_record
// - Push record into m_records.
// - If BUILD_DEBUG is defined, print:
//   [BuildDebug] module=<name>, time=<time>s, success=<true/false>

// TODO: avg_success_time
// - Compute average compile_time for records where success==true.
// - Return 0 if none are successful.

// TODO: success_rate
// - Return percentage (0–100) of successful modules among all records.

// TODO: save_report
// - Write a formatted report to m_path in this form:
//   --- Build Report ---
//   total modules: 3
//   success: 2 (66.67%)
//   avg success time: 1.35s
//   modules:
//     core.cpp -> 1.23s [OK]
//     util.cpp -> 1.47s [OK]
//     net.cpp  -> 2.01s [FAIL]

// TODO: clear
// - Clear m_records and truncate the log file.

// TODO: summary
// - Return compact info like:
//   "3 modules, 66.7% success, avg=1.35s"
