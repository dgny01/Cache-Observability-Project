#include "analyzer.hpp"
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <iomanip>

using namespace std;

double measure_latency(size_t size_bytes) {
    size_t array_size = size_bytes / sizeof(size_t);
    vector<size_t> data(array_size);

    for (size_t i = 0; i < array_size; ++i) {
        data[i] = (i + 16) % array_size;
    }

    volatile size_t idx = 0;
    const size_t iterations = 10'000'000;

    auto start = chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; ++i) {
        idx = data[idx];
    }
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, nano> diff = end - start;
    return diff.count() / iterations;
}

void run_simulation(const LatencyMetrics& m) {
    const int total_requests = 100000;
    double total_time_with_cache = 0;
    int hits[4] = {0, 0, 0, 0};

    for (int i = 0; i < total_requests; i++) {
        int chance = rand() % 100;
        if (chance < 90) { hits[0]++; total_time_with_cache += m.l1; }
        else if (chance < 96) { hits[1]++; total_time_with_cache += m.l2; }
        else if (chance < 99) { hits[2]++; total_time_with_cache += m.l3; }
        else { hits[3]++; total_time_with_cache += m.ram; }
    }

    double time_without_cache = total_requests * m.ram;

    cout << fixed << setprecision(2);
    cout << "\n--- SIMULATION REPORT ---" << endl;
    cout << "Execution Time (With Cache):    " << total_time_with_cache / 1e6 << " ms" << endl;
    cout << "Execution Time (Without Cache): " << time_without_cache / 1e6 << " ms" << endl;
    cout << "PERFORMANCE BOOST: " << (1.0 - (total_time_with_cache / time_without_cache)) * 100 << "%" << endl;
}