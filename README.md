# LLTS: Low-Latency Trading System

A simplified low-latency trading system written in C++20, built as a learning project.
It runs an exchange simulator with a matching engine, a binary market data feed,
a book builder, a market-making strategy, pre-trade risk checks and an order gateway,
connected by lock-free queues across pinned threads.

## Requirements

- CMake 3.28 or later
- A C++20 compiler: GCC 13+, Clang 17+ or Apple Clang 15+
- Linux or macOS

GoogleTest and Google Benchmark are downloaded automatically when the project is configured.

## Build and test

The project has four build presets:

| Preset    | Purpose                                   |
| --------- | ----------------------------------------- |
| `debug`   | Normal debug build                        |
| `asan`    | Debug build with AddressSanitizer and UBSan |
| `tsan`    | Debug build with ThreadSanitizer          |
| `release` | Optimised build with debug information    |

From the repository root:

```bash
cmake --preset debug
cmake --build --preset debug
ctest --preset debug
```

Replace `debug` with any other preset name. Each preset builds into `build/<preset>`.

In CLion, the presets appear as CMake profiles (Settings → Build, Execution,
Deployment → CMake).