#include <iostream>
#include <ctime>
#include <iomanip>
#include "analyzer.hpp"

using namespace std;

int main() {
    srand(time(0));
    cout << "===============================================" << endl;
    cout << "  MASTER CACHE ANALYZER & SIMULATOR (v1.0)     " << endl;
    cout << "===============================================" << endl;
    cout << "[1/2] Benchmarking Hardware Latencies..." << endl;


    LatencyMetrics metrics;
    metrics.l1 = measure_latency(16 * 1024);
    metrics.l2 = measure_latency(256 * 1024);
    metrics.l3 = measure_latency(4 * 1024 * 1024);
    metrics.ram = measure_latency(128 * 1024 * 1024);   

    cout << fixed << setprecision(2);
    cout << "Measurement Complete:" << endl;
    cout << " > L1 Latency:  " << metrics.l1 << " ns" << endl;
    cout << " > L2 Latency:  " << metrics.l2 << " ns" << endl;
    cout << " > L3 Latency:  " << metrics.l3 << " ns" << endl;
    cout << " > RAM Latency: " << metrics.ram << " ns" << endl;

    cout << "\n[2/2] Starting Simulation with Real-World Metrics..." << endl;


    run_simulation(metrics);

    cout << "Note: Phase 2 will integrate eBPF & PMU for live HW counters." << endl;

    return 0;
}