#ifndef MATHLIB_HPP
#define MATHLIB_HPP

#include <string>
#include <vector>

namespace csi::math {

// Public API functions (library exports)
extern "C" {
    double add(double a, double b);
    double mul(double a, double b);
    double mean(const double* arr, int size);
}

// Version info for ABI check
std::string version();

}

#endif
