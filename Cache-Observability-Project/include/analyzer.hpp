#ifndef ANALYZER_HPP
#define ANALYZER_HPP

#include <vector>


struct LatencyMetrics {
    double l1, l2, l3, ram;
};


double measure_latency(size_t size_bytes);
void run_simulation(const LatencyMetrics& m);

#endif