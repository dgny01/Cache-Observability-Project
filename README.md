# Cache-Observability-Project (v1.0)

A high-performance system analysis tool designed to bridge the gap between **Software Logic** and **Hardware Reality**. This project measures real-world memory latencies and simulates cache hierarchy performance, with a roadmap toward **eBPF-powered hardware counter** integration.

---

## Overview

Modern software performance is often bottlenecked by the memory hierarchy (L1, L2, L3, and RAM). This project provides:
1. **Hardware Benchmarking:** Using **Pointer Chasing** to bypass CPU prefetchers and measure real nanosecond-level latencies.
2. **Performance Simulation:** Analyzing how Cache Hit/Miss ratios affect execution time using real-world hardware metrics.
3. **Observability Roadmap:** Transitioning from software-only simulation to **eBPF & PMU (Performance Monitoring Unit)** integration to capture live hardware events.



---

## Features

* **Bypassing Prefetchers:** Implements a `volatile` pointer chasing engine to ensure the CPU cannot "guess" the next memory address, yielding authentic latency data.
* **Memory Hierarchy Awareness:** Specifically targets typical L1 (16KB), L2 (256KB), L3 (4MB), and RAM (128MB+) boundaries.
* **Efficiency Analysis:** Calculates the "Performance Boost" provided by the cache system compared to raw RAM access.
* **Dockerized Monitoring:** Ready to be integrated with **Prometheus & Grafana** for real-time visualization of system stress.

---

## Quick Start

### Prerequisites
* GCC/G++ Compiler
* Linux Environment (Recommended for Phase 2 eBPF features)

### Build & Run
```bash
# Clone the repository
git clone [https://github.com/dgny01/Cache-Observability-Project.git](https://github.com/dgny01/Cache-Observability-Project.git)

# Navigate to the project directory
cd Cache-Observability-Project

# Compile the analyzer
g++ -O3 main.cpp -o cache_analyzer

# Run the simulation
./cache_analyzer
```


Roadmap & eBPF Integration
This project is evolving following a structured systems engineering path:

[x] Phase 1: C++ Memory Latency Benchmarking & Simulation.

[ ] Phase 2: Integration of bpftrace for VFS-level event capturing.

[ ] Phase 3: Using perf_event_open via eBPF to access Hardware Performance Counters (PMU).

[ ] Phase 4: Live dashboard comparing Predicted Hit Rate vs. Actual HW Cache Misses.


Acknowledgments
Special thanks to Uğur Hoca for the guidance on perf_event_open and hardware counter strategies (L1D, L1I, and LLC monitoring). This project aims to contribute to the system programming community as a tutorial-grade exercise.


Author
Doğanay Yıldız 3rd Year Computer Engineering Student GitHub | LinkedIn

Measuring the invisible at the kernel level.
