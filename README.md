Cache-Observability-Project (v1.1) 

A high-performance system analysis tool designed to bridge the gap between Software Logic and Hardware Reality. This project measures real-world memory latencies across the CPU cache hierarchy using advanced systems programming techniques.

🔍 Overview

Modern software performance is often bottlenecked by the memory hierarchy. This tool provides an empirical look at how data travels between the CPU and RAM.

Hardware Benchmarking: Uses Random Pointer Chasing to bypass CPU hardware prefetchers, ensuring authentic nanosecond-level latency data.

Hierarchy Awareness: Specifically targets and identifies transitions between L1, L2, L3 caches, and Main RAM.

Observability Ready: Engineered to export structured data (CSV/JSON) for integration with modern monitoring stacks like Prometheus and Grafana.

 Features

Prefetcher Defeat: Implements a volatile pointer chasing engine. By making the next memory address dependent on the current one in a shuffled array, we force the CPU to wait for the full round-trip time.

Modular Architecture: Cleanly separated into benchmark, simulator, and report modules for high maintainability.

CLI Interface: Fully controllable via command-line arguments (size, iterations, sweep modes).

Automated Sweep: A one-command mode to map the entire memory subsystem of the host machine.

🛠️ Build & Run

Prerequisites

GCC/G++ Compiler

Make build tool

Linux Environment (Recommended for performance counter accuracy)

Compilation

The project uses a Makefile to manage the build process. The binary is generated in the build/ directory to keep the workspace clean.

# Compile the project
make


Usage Examples

You can run the analyzer with different flags to target specific memory regions or run a full sweep.

# 1. Automated Hierarchy Sweep (Recommended)
./build/cache_analyzer --all

# 2. Test a specific buffer size (e.g., 2MB)
./build/cache_analyzer -s 2097152

# 3. Custom Iterations (For higher precision)
./build/cache_analyzer --all -i 50000000


 Understanding the Physics

Engineering Note on RAM Latency:

Note: You will notice RAM latency values around 80-120ns. This is a sign of measurement accuracy. By using random access patterns, we bypass the CPU's ability to "predict" the next data block (Prefetching). This reveals the true physical latency of the DRAM cells, which is the ultimate bottleneck in modern computing.

 Roadmap & eBPF Integration

This project follows a structured systems engineering evolution:

[x] Phase 1: C++ Memory Latency Benchmarking (Modular & CLI-ready).

[ ] Phase 2: Integration of bpftrace for VFS and Memory-level event capturing.

[ ] Phase 3: Using perf_event_open via eBPF to access PMU (Performance Monitoring Units) for L1/LLC Cache Miss tracking.

Prerequisites

GCC/G++ Compiler

Make build tool

Linux Environment (Recommended for performance counter accuracy)

Compilation

The project uses a Makefile to manage the build process. The binary is generated in the build/ directory to keep the workspace clean.

# Compile the project
make


Usage Examples
# 1. Automated Hierarchy Sweep (Recommended)
./build/cache_analyzer --all

# 2. Test a specific buffer size (e.g., 2MB)
./build/cache_analyzer -s 2097152

# 3. Custom Iterations (For higher precision)
./build/cache_analyzer --all -i 50000000


📊 Understanding the Physics

Engineering Note on RAM Latency:

Note: You will notice RAM latency values around 80-120ns. This is a sign of measurement accuracy. By using random access patterns, we bypass the CPU's ability to "predict" the next data block (Prefetching). This reveals the true physical latency of the DRAM cells, which is the ultimate bottleneck in modern computing.

🗺️ Roadmap & eBPF Integration

This project follows a structured systems engineering evolution:

[x] Phase 1: C++ Memory Latency Benchmarking (Modular & CLI-ready).

[ ] Phase 2: Integration of bpftrace for VFS and Memory-level event capturing.

[ ] Phase 3: Using perf_event_open via eBPF to access PMU (Performance Monitoring Units) for L1/LLC Cache Miss tracking.

[ ] Phase 4: Live Grafana dashboard comparing Software Simulations vs. Actual Hardware Events.

 Acknowledgments

Special thanks to the system programming community and mentors for insights into perf_event_open and hardware counter strategies.

Author: Doğanay Yıldız
3rd Year Computer Engineering Student "Measuring the invisible at the kernel level."
[ ] Phase 4: Live Grafana dashboard comparing Software Simulations vs. Actual Hardware Events.

 Acknowledgments

Special thanks to the system programming community and mentors for insights into perf_event_open and hardware counter strategies.

Author: Doğanay Yıldız

3rd Year Computer Engineering Student "Measuring the invisible at the kernel level."
