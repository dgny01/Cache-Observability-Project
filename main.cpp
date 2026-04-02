#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <iomanip>

using namespace std;

/**
 * SECTION 1: HARDWARE BENCHMARK ENGINE
 * Measures real hardware latency using Pointer Chasing to bypass the CPU prefetcher.
 */
double measure_latency(size_t size_bytes) {
    size_t array_size = size_bytes / sizeof(size_t);
    vector<size_t> data(array_size);

    // Initialize for Pointer Chasing
    for (size_t i = 0; i < array_size; ++i) {
        data[i] = (i + 16) % array_size;
    }

    volatile size_t idx = 0; // Prevent compiler optimizations
    const size_t iterations = 10'000'000;

    auto start = chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; ++i) {
        idx = data[idx];
    }
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, nano> diff = end - start;
    return diff.count() / iterations; // Nanoseconds per access
}

/**
 * SECTION 2: CACHE HIERARCHY SIMULATOR
 * Simulates performance based on measured hardware latencies.
 */
void run_simulation(double l1, double l2, double l3, double ram) {
    const int total_requests = 100000;
    double total_time_with_cache = 0;
    int hits[4] = {0, 0, 0, 0}; // L1, L2, L3, RAM

    // Simulated hit rate probabilities (To be replaced by eBPF/PMU metrics later)
    for (int i = 0; i < total_requests; i++) {
        int chance = rand() % 100;
        if (chance < 90) { // 90% L1 Hit
            hits[0]++;
            total_time_with_cache += l1;
        } else if (chance < 96) { // 6% L2 Hit
            hits[1]++;
            total_time_with_cache += l2;
        } else if (chance < 99) { // 3% L3 Hit
            hits[2]++;
            total_time_with_cache += l3;
        } else { // 1% RAM Access (Miss)
            hits[3]++;
            total_time_with_cache += ram;
        }
    }

    double time_without_cache = total_requests * ram;

    cout << "\n--------------------------------------------------" << endl;
    cout << " SIMULATION REPORT (" << total_requests << " Accesses)" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "L1 Hits:   " << hits[0] << " | L2 Hits: " << hits[1] << endl;
    cout << "L3 Hits:   " << hits[2] << " | RAM Miss: " << hits[3] << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "Execution Time (With Cache):    " << fixed << setprecision(2) << total_time_with_cache / 1e6 << " ms" << endl;
    cout << "Execution Time (Without Cache): " << time_without_cache / 1e6 << " ms" << endl;
    cout << "PERFORMANCE BOOST: " << (1.0 - (total_time_with_cache / time_without_cache)) * 100 << "%" << endl;
    cout << "--------------------------------------------------\n" << endl;
}

int main() {
    srand(time(0));
    cout << "===============================================" << endl;
    cout << "  MASTER CACHE ANALYZER & SIMULATOR (v1.0)     " << endl;
    cout << "===============================================" << endl;
    cout << "[1/2] Benchmarking Hardware Latencies..." << endl;

    // Measuring latencies for different levels of the memory hierarchy
    double l1 = measure_latency(16 * 1024);            // 16KB (Likely L1)
    double l2 = measure_latency(256 * 1024);           // 256KB (Likely L2)
    double l3 = measure_latency(4 * 1024 * 1024);      // 4MB (Likely L3)
    double ram = measure_latency(128 * 1024 * 1024);   // 128MB (Main Memory)

    cout << "Measurement Complete:" << endl;
    cout << " > L1 Latency: " << setprecision(2) << l1 << " ns" << endl;
    cout << " > L2 Latency: " << l2 << " ns" << endl;
    cout << " > L3 Latency: " << l3 << " ns" << endl;
    cout << " > RAM Latency: " << ram << " ns" << endl;

    cout << "\n[2/2] Starting Simulation with Real-World Metrics..." << endl;
    run_simulation(l1, l2, l3, ram);

    cout << "Note: Phase 2 will integrate eBPF & PMU for live HW counters." << endl;

    return 0;
}