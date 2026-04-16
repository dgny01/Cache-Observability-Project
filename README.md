# CacheScope

<img width="1824" height="881" alt="Ekran Görüntüsü - 2026-04-13 20-51-24" src="https://github.com/user-attachments/assets/91f92010-8fc0-4141-8b94-6f0fd3498745" />

## 🏗 Architecture Diagram

<pre>
┌───────────────────────────────────────────────────────────────────────────────┐
│                    Cache-Observability-Project (v1.2)                          │
│        High-Performance Cache Hierarchy Benchmark + Observability Stack        │
└───────────────────────────────────────────────────────────────────────────────┘

                                ┌───────────────────────┐
                                │        User CLI        │
                                │ --all --size -i --help │
                                └───────────┬───────────┘
                                            │
                                            ▼
┌───────────────────────────────────────────────────────────────────────────────┐
│                           Benchmark Controller (C++)                           │
│  - Scenario selection (L1/L2/L3/RAM)                                           │
│  - Buffer scaling & iteration control                                          │
│  - Run orchestration                                                           │
└───────────────────────────────┬──────────────────────────────────────────────┘
                                │
                                ▼
┌───────────────────────────────────────────────────────────────────────────────┐
│                    Pointer Chasing Engine (Prefetcher Defeat)                  │
│  - Randomized linked-list traversal                                            │
│  - Cache-miss enforcement                                                      │
│  - Nanosecond timing measurements                                              │
└───────────────────────────────┬──────────────────────────────────────────────┘
                                │
                                ▼
┌───────────────────────────────────────────────────────────────────────────────┐
│                         Latency Analytics / Aggregation                        │
│  - avg_ns = total_time / iterations                                            │
│  - hierarchy transition detection                                               │
│  - jitter / noise extraction (optional)                                        │
└───────────────────────────────┬──────────────────────────────────────────────┘
                                │
                                ├─────────────────────────────────────────┐
                                │                                         │
                                ▼                                         ▼
                  ┌─────────────────────────────┐          ┌─────────────────────────────┐
                  │   PSI Pressure Reader        │          │   eBPF Tracing Layer         │
                  │  /proc/pressure/*            │          │ (Planned - Phase 3)          │
                  │  cpu / memory / io           │          │ - context switches           │
                  └──────────────┬──────────────┘          │ - interrupts                 │
                                 │                         │ - scheduler delays           │
                                 └──────────────┬──────────┴─────────────────────────────┘
                                                ▼
┌───────────────────────────────────────────────────────────────────────────────┐
│                        Prometheus Metrics Exporter (/metrics)                  │
│  latency_ns{level="L1"}   latency_ns{level="L2"}   latency_ns{level="L3"}      │
│  latency_ns{level="RAM"}  psi_cpu  psi_mem  psi_io                              │
└───────────────────────────────┬──────────────────────────────────────────────┘
                                │ scrape
                                ▼
┌───────────────────────────────────────────────────────────────────────────────┐
│                                 Prometheus                                     │
│                          Time-Series Metrics Storage                            │
└───────────────────────────────┬──────────────────────────────────────────────┘
                                │ query
                                ▼
┌───────────────────────────────────────────────────────────────────────────────┐
│                                  Grafana                                       │
│                   Live Hardware Latency Visualization Dashboard                 │
└───────────────────────────────────────────────────────────────────────────────┘

                   ┌──────────────────────────────────────────────────┐
                   │            Docker Compose Deployment              │
                   │   Analyzer + Prometheus + Grafana (Single Stack)  │
                   └──────────────────────────────────────────────────┘
</pre>

**A high-performance system analysis tool designed to bridge the gap between Software Logic and Hardware Reality.**  
This project measures real-world memory latencies across the CPU cache hierarchy and correlates them with kernel-level events.

> **"Measuring the invisible at the kernel level."**

---

##  Overview

Modern software performance is often bottlenecked by the **memory hierarchy** rather than CPU instructions.  
This tool provides an **empirical** view of how data travels between CPU caches and main memory, featuring a full observability stack.

It combines:

- **Low-level C++ benchmarking**
- **Random pointer chasing to bypass prefetchers**
- **Prometheus metrics exporting**
- **Grafana dashboards**
- **Kernel pressure awareness (PSI)**
- *(Upcoming)* eBPF kernel tracing for context-switch correlation

---

##  Key Goals

- Measure real-world latency differences between **L1, L2, L3 and RAM**
- Defeat CPU prediction mechanisms (prefetchers)
- Export structured benchmark results into an observability stack
- Visualize hardware performance signatures live
- Correlate benchmark noise with kernel events (context switches, PSI pressure)

---

##  Why This Matters

Even perfectly optimized software can stall if memory access becomes slow.  
Understanding cache transitions is crucial for:

- high-frequency trading systems
- kernel-level performance engineering
- low-latency infrastructure
- game engines & physics engines
- distributed systems

---

##  Features

###  Hardware Benchmarking (Pointer Chasing Engine)
Uses **Random Pointer Chasing** to bypass hardware prefetchers, ensuring authentic nanosecond-level latency measurements.

###  Hierarchy Awareness
Targets and identifies transitions between:

- L1 Cache
- L2 Cache
- L3 Cache
- Main RAM

###  Observability Ready
Exports benchmark metrics into **Prometheus**, visualized via **Grafana**.

### Dockerized Stack
Deploy analyzer + Prometheus + Grafana with one command.

###  CLI Interface
Fully controllable via flags:

- `--all`
- `--size`
- `--iterations`

### PSI (Pressure Stall Information) Integration *(Experimental)*
Reads Linux PSI data to observe CPU/memory pressure during benchmarks.

### eBPF Kernel Insight *(Planned)*
Future phase will capture context switches and interrupts during measurements using kprobes.

---

## Measurement Physics & “Noise”

You may notice RAM latency values around **80–120ns**.  
That’s not an error — it is a sign of measurement authenticity.

Because access patterns are randomized, the CPU cannot “predict” the next memory address, which forces real hardware latency.

However, user-space benchmarks are affected by **kernel noise**:

- interrupts
- context switches
- scheduler overhead

This project aims to isolate and quantify these effects using **eBPF tracing**.

---

## Expected vs Real Latency Table

This table shows realistic expectations and how your tool confirms real hardware behavior:

| Memory Level | Typical Size | Expected Latency | Measured Latency (Your Tool) | Status |
|------------|--------------|------------------|------------------------------|--------|
| L1 Cache | 32 - 64 KB | ~1-2 ns | 1.2 ns | ✅ Optimal |
| L2 Cache | 256 - 512 KB | ~3-5 ns | 4.1 ns | ✅ Optimal |
| L3 Cache | 8 - 16 MB | ~10-20 ns | 14.5 ns | ✅ Optimal |
| Main RAM | 8 GB+ | ~80-120 ns | 98 ns | ✅ Authentic |

---

##  How It Works (Pointer Chasing Logic)

### Why Pointer Chasing?

CPUs are smart; they use **Hardware Prefetchers** to predict upcoming memory access and load data early.  
This makes normal benchmarks misleading.

To measure true latency, we must be unpredictable.

By using a **shuffled linked-list pattern**, the next address becomes dependent on the current loaded value.  
The CPU cannot guess the next jump, forcing it to wait for the real hardware round-trip.

This reveals the actual latency of:

- cache hits
- cache misses
- DRAM access

---

##  Project Architecture

- **Benchmark Engine (C++)**
  - volatile pointer chasing
  - timing & iteration measurement
  - cache-size scaling tests
- **Metrics Exporter**
  - Prometheus endpoint
- **Observability Stack**
  - Prometheus scraping
  - Grafana dashboard visualization
- **Experimental Kernel Layer**
  - PSI data collection
  - future eBPF integration

---

##  Testing Architecture (Planned)

Unit testing will be implemented using **GoogleTest** in the next iterations.

Planned scenarios:

### 1) Math Validation
Validate that latency calculations are correct:

- `latency_ns = total_time / iterations`

### 2) Boundary Checks
Ensure that if buffer size exceeds cache limits or RAM constraints:

- no segmentation faults
- no undefined behavior
- clean failure behavior

### 3) Simulated vs Real Validation
Verify that simulation mode produces expected distributions:

- cache-level clustering
- stable mean latency
- predictable variance patterns

---

##  Build & Run

### Prerequisites

- Linux Environment *(recommended for accurate counters & timing)*
- Docker & Docker Compose
- `g++` compiler *(for local builds)*

---

## ⚡ Quick Start (Observability Stack)

To launch the analyzer with Prometheus + Grafana:

```bash
docker-compose up --build
```
Then access:

Grafana: http://localhost:3000
Prometheus: http://localhost:9090

Local CLI Usage

Build locally:
```bash
make
```

Run full benchmark:
```bash
./build/cache_analyzer --all -i 50000000
```

Sample Output

$ ./build/cache_analyzer --all -i 50000000

[Cache Analyzer v1.2]
Mode: Full Hierarchy Scan
Iterations: 50000000
CPU: Intel(R) Core(TM) i7-11800H

---------------------------------------------------
[L1 Cache Test]
Buffer Size: 64 KB
Avg Latency: 1.2 ns

[L2 Cache Test]
Buffer Size: 512 KB
Avg Latency: 4.1 ns

[L3 Cache Test]
Buffer Size: 16 MB
Avg Latency: 14.5 ns

[Main RAM Test]
Buffer Size: 512 MB
Avg Latency: 98.0 ns
---------------------------------------------------

[PSI Metrics]
CPU Pressure: 0.00
Memory Pressure: 0.12
IO Pressure: 0.00

[Prometheus Exporter]
Metrics available at: http://localhost:8080/metrics

Roadmap
✅ Phase 1: C++ Modular CLI & Benchmarking Engine
✅ Phase 2: Dockerization & Prometheus/Grafana Integration
Phase 3: eBPF Integration (kprobes) to capture context switches during benchmarks
Phase 4: Comparative Analysis: Software Simulations vs Actual Hardware Events

 Acknowledgments

Special thanks to:

the systems programming community
Rafael David Tinoco for kernel isolation insights
my mentors at Kloia for guidance on observability patterns

uthor

Doğanay Yıldız
3rd Year Computer Engineering Student

"Measuring the invisible at the kernel level."
