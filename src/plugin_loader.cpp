#include "plugin_loader.hpp"
#include <iostream>
#include <dlfcn.h>     // On Linux (students can adjust for Windows with LoadLibrary)
#include <stdexcept>

// TODO: Implement constructor
// - Load the shared library using dlopen(lib_path.c_str(), RTLD_LAZY)
// - Get function pointers using dlsym for add, mul, mean, version
// - If any symbol is missing, print error and set handle=nullptr

// TODO: Implement destructor
// - If handle is not null, call dlclose(handle)

// TODO: Implement is_loaded()
// - Return true if handle is not null

// TODO: Implement get_version()
// - Call f_version() if available, else return "Unknown"

// TODO: Implement call_add / call_mul / call_mean
// - Call respective function pointers safely (if null, throw runtime_error)
