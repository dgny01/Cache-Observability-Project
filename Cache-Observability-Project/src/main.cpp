#include <iostream>
#include <getopt.h>
#include <string>
#include <vector>
#include <iomanip> 
#include "analyzer.hpp"

using namespace std;

void print_help() {
    cout << "Usage: ./cache_analyzer [options]\n"
         << "Options:\n"
         << "  -s, --size <bytes>    Specific memory size to test\n"
         << "  -i, --iter <count>    Number of iterations (default: 10M)\n"
         << "  -a, --all             Sweep all cache levels (L1 to RAM)\n"
         << "  -h, --help            Show this help message\n";
}

int main(int argc, char* argv[]) {
    Config conf;
    int opt;
    bool sweep_mode = true;

    static struct option long_options[] = {
        {"size", required_argument, 0, 's'},
        {"iter", required_argument, 0, 'i'},
        {"all",  no_argument,       0, 'a'},
        {"help", no_argument,       0, 'h'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "s:i:ah", long_options, NULL)) != -1) {
        switch (opt) {
            case 's':
                conf.buffer_size = stoll(optarg);
                sweep_mode = false; 
                break;
            case 'i': conf.iterations = stoll(optarg); break;
            case 'a': sweep_mode = true; break;
            case 'h': print_help(); return 0;
            default: print_help(); return 1;
        }
    }

    cout << "--- CACHE HIERARCHY ANALYSIS STARTING ---" << endl;
    cout << "Iterations per test: " << conf.iterations << endl << endl;

    // Tablo başlığı
    cout << left << setw(15) << "LEVEL" << setw(15) << "SIZE" << "LATENCY" << endl;
    cout << "---------------------------------------------" << endl;

    if (sweep_mode) {
       
        vector<pair<string, size_t>> levels = {
            {"L1 Cache", 16 * 1024},          
            {"L1/L2 Border", 64 * 1024},      
            {"L2 Cache", 256 * 1024},         
            {"L3 Cache", 4 * 1024 * 1024},    
            {"Main RAM", 128 * 1024 * 1024}  
        };

        for (const auto& level : levels) {
            conf.buffer_size = level.second;
            Result res = measure_latency(conf);

            cout << left << setw(15) << level.first
                 << setw(15) << to_string(level.second / 1024) + " KB"
                 << fixed << setprecision(3) << res.latency_ns << " ns" << endl;
        }
    } else {
        // Kullanıcının girdiği tekli ölçüm
        Result res = measure_latency(conf);
        cout << left << setw(15) << "Custom"
             << setw(15) << to_string(conf.buffer_size / 1024) + " KB"
             << fixed << setprecision(3) << res.latency_ns << " ns" << endl;
    }

    cout << "---------------------------------------------" << endl;
    cout << "Analysis Complete." << endl;

    return 0;
}
