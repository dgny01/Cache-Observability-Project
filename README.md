Cache-Observability-Project (v1.2) 
A high-performance system analysis tool designed to bridge the gap between Software Logic and Hardware Reality. This project measures real-world memory latencies across the CPU cache hierarchy and correlates them with kernel-level events.

 Overview
Modern software performance is often bottlenecked by the memory hierarchy. This tool provides an empirical look at how data travels between the CPU and RAM, now featuring a full observability stack.

Hardware Benchmarking: Uses Random Pointer Chasing to bypass CPU hardware prefetchers, ensuring authentic nanosecond-level latency data.

Hierarchy Awareness: Specifically targets and identifies transitions between L1, L2, L3 caches, and Main RAM.

Observability Ready: Engineered to export structured data to Prometheus and visualize it via Grafana in a Dockerized environment.

Kernel Insight: Explores the impact of Context Switches and Resource Pressure (PSI) on micro-latency measurements.

 Features
Prefetcher Defeat: Implements a volatile pointer chasing engine to reveal the true physical latency of the DRAM cells.

Live Monitoring: Fully integrated with Prometheus and Grafana. View your hardware's performance signature in real-time.

Dockerized Stack: Deploy the analyzer, database, and dashboard with a single command.

CLI Interface: Fully controllable via command-line arguments (--all, --size, --iterations).

Resource Pressure (PSI) Aware: (Experimental) Integration of Linux Pressure Stall Information to monitor system health under load.

 Build & Run
Prerequisites
Docker & Docker Compose

G++ Compiler (for local builds)

Linux Environment (Required for performance counter accuracy)

Quick Start (Observability Stack)
To launch the analyzer along with the Grafana dashboard:

Bash
docker-compose up --build
Grafana: http://localhost:3000

Prometheus: http://localhost:9090

Local CLI Usage
Bash
make
./build/cache_analyzer --all -i 50000000
 Measurement Physics & "Noise" Note
You will notice RAM latency values around 80-120ns. This is a sign of measurement accuracy. By using random access patterns, we bypass the CPU's ability to "predict" data (Prefetching).

Technical Challenge: User-space benchmarks are subject to "Kernel Noise". Interrupts and context switches can inject micro-delays into the measurements. This project aims to isolate these factors using eBPF.

🗺 Roadmap
[x] Phase 1: C++ Modular CLI & Benchmarking Engine.

[x] Phase 2: Dockerization & Prometheus/Grafana Integration.

[ ] Phase 3: eBPF Integration (kprobes) to capture kernel-level context switches during benchmarks.

[ ] Phase 4: Comparative Analysis: Software Simulations vs. Actual Hardware Events.

 Acknowledgments
Special thanks to the systems programming community, Rafael David Tinoco for kernel isolation insights, and my mentors at Kloia for their guidance on observability patterns.

 Author
Doğanay Yıldız 3rd Year Computer Engineering Student 
"Measuring the invisible at the kernel level."
