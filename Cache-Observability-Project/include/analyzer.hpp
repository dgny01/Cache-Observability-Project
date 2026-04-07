#ifndef ANALYZER_HPP
#define ANALYZER_HPP

#include <cstddef>

struct Config {
    size_t buffer_size = 1024 * 1024;
    size_t iterations = 10000000;
};

struct Result {
    double latency_ns;
    size_t size_bytes;
};

Result measure_latency(const Config& conf);
void run_simulation(double l1, double l2, double l3, double ram);

#endif