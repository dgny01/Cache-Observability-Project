#include "analyzer.hpp"
#include <vector>
#include <chrono>
#include <algorithm>
#include <random>

using namespace std;

Result measure_latency(const Config& conf) {
    size_t array_size = conf.buffer_size / sizeof(size_t);
    if (array_size < 1) array_size = 1;

    vector<size_t> data(array_size);
    for (size_t i = 0; i < array_size; ++i) data[i] = i;

    shuffle(data.begin(), data.end(), mt19937(random_device()()));

    volatile size_t idx = 0;
    auto start = chrono::high_resolution_clock::now();

    for (size_t i = 0; i < conf.iterations; ++i) {
        idx = data[idx];
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, nano> diff = end - start;

    return { diff.count() / conf.iterations, conf.buffer_size };
}