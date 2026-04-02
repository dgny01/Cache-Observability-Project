#include <iostream>
#include <vector>
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


void run_simulation(double l1, double l2, double l3, double ram) {
    const int total_requests = 100000;
    double total_time_with_cache = 0;
    int hits[4] = {0, 0, 0, 0}; 

  
    for (int i = 0; i < total_requests; i++) {
        int chance = rand() % 100;
        if (chance < 90) { 
            hits[0]++;
            total_time_with_cache += l1;
        } else if (chance < 96) { 
            hits[1]++;
            total_time_with_cache += l2;
        } else if (chance < 99) { 
            hits[2]++;
            total_time_with_cache += l3;
        } else {
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

   
    double l1 = measure_latency(16 * 1024);            
    double l2 = measure_latency(256 * 1024);           
    double l3 = measure_latency(4 * 1024 * 1024);      
    double ram = measure_latency(128 * 1024 * 1024); 

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
