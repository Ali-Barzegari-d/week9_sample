#ifndef PLUGIN_LOADER_HPP
#define PLUGIN_LOADER_HPP

#include <string>
#include <functional>

namespace csi::plugin {

// Function pointer types for the plugin functions
using AddFunc = double(*)(double,double);
using MulFunc = double(*)(double,double);
using MeanFunc = double(*)(const double*, int);

// Represents a dynamically loaded math plugin
class PluginLoader {
public:
    explicit PluginLoader(const std::string& lib_path);
    ~PluginLoader();

    bool is_loaded() const;
    std::string get_version() const;

    double call_add(double a, double b);
    double call_mul(double a, double b);
    double call_mean(const double* arr, int size);

private:
    void* handle = nullptr;
    AddFunc f_add = nullptr;
    MulFunc f_mul = nullptr;
    MeanFunc f_mean = nullptr;
    std::string (*f_version)() = nullptr;
};

} // namespace csi::plugin

#endif
