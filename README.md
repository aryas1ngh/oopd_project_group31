# 📡 Cellular Network Simulator (Threaded)

![C++](https://img.shields.io/badge/Language-C++17-blue.svg?style=flat&logo=c%2B%2B)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20macOS%20%7C%20WSL-lightgrey.svg?style=flat)
![Build](https://img.shields.io/badge/Build-Make-green.svg)

A high-performance, multi-threaded cellular network simulator built in C++ without using the standard library (STL) for core I/O and logic. This project simulates various mobile network generations (2G, 3G, 4G, 5G) by managing concurrent user connections via custom threading wrappers and system calls.

---

## 🌟 Features

- **🚫 No-STL I/O**: Uses custom `Basicio` wrapper around Linux/macOS system calls (`sys_read`, `sys_write`) for console Input/Output.
- **🧵 Multi-threaded Simulation**: Simulates concurrent user requests on cell towers using custom threaded tower classes.
- **📊 Detailed Analysis**: Generates detailed bandwidth allocation reports, core overhead calculations, and user mapping for 2G, 3G, 4G, and 5G networks.
- **🖥️ Menu-Driven Interface**: Interactive console UI to load users, select specific simulations, or run full diagnostics.
- **🍏 Cross-Platform Support**: Supports **Linux/Windows (via WSL)** and **macOS** (Apple Silicon & Intel) with architecture-specific assembly and Makefiles.

---

## 📂 Project Structure

~~~text
├── Basicio.cpp / .h        # Custom I/O using syscalls
├── CellTower.hpp           # Base tower logic
├── ThreadedCellTower.hpp   # Multi-threaded tower logic
├── ThreadedTowers.hpp      # Specific 2G/3G/4G/5G implementations
├── UserDevice.hpp          # User entity class
├── main.cpp                # Entry point and Menu UI
├── Makefile                # Build script for Linux/WSL
├── syscall.s               # Assembly syscalls for Linux (x86_64)
├── users.txt               # Sample user data file
└── macos/                  # macOS specific files
    ├── Makefile            # Adjusted Makefile for macOS
    └── syscall.s           # Assembly syscalls for macOS (M1/M2/Intel)

~~~

## 🏗️ Architectural Design (OOPS)

The project relies heavily on **Object-Oriented Programming (OOP)** principles to ensure modularity, scalability, and code reuse.

### 🧬 Inheritance
- **Base Class**: The `CellTower` class defines the fundamental properties (Total Bandwidth, Channel Width, Antenna Count).
- **Intermediate Class**: `ThreadedCellTower` inherits from `CellTower` to add concurrency capabilities (worker threads, mutexes for thread-safe operations).
- **Derived Classes**: Specific generations (`ThreadedTower2G`, `ThreadedTower3G`, `ThreadedTower4G`, `ThreadedTower5G`) inherit from `ThreadedCellTower` to implement specific network standards and configurations.

### 🎭 Polymorphism
- **Virtual Functions**: Key methods like `simulate()`, `calculateTotalCapacity()`, and `printStats()` are virtual functions.
- **Unified Execution**: This allows the main simulation loop to treat all tower generations uniformly (via base class pointers) while executing the generation-specific logic dynamically at runtime.

### 📦 Encapsulation & Data Hiding
- **Access Control**: Core data structures like `channels` and `frequency maps` are protected or private, accessible only through controlled public interfaces.
- **Abstraction**: `UserDevice` encapsulates user identity and connection status, exposing only necessary data (like ID) to the network simulation while hiding internal state.

### 🔌 Data Abstraction
- **simplified Interfaces**: The complex low-level logic of frequency division, thread synchronization, and syscall management is hidden behind simple high-level interfaces like `runFullSimulation()` and `addUser()`.


## 🧩 Key Components

The simulation is built around three primary class types:

### 1. 📱 User Device (`UserDevice.hpp`)
Represents a mobile subscriber in the network.

- **Role**: Stores unique identifiers (IMSI/ID) and connection status.
- **Interaction**: Requests attachment to a specific frequency channel on the Cell Tower.
- **Encapsulation**: Hides internal state while exposing only necessary information like user ID to the network simulation.

### 2. 📡 Cell Tower (`CellTower.hpp` / `ThreadedTowers.hpp`)
The central entity managing radio resources.

- **Role**: Allocates frequency channels, manages bandwidth, and handles user connections concurrently using worker threads.
- **Logic**: Splits total bandwidth into specific channels based on the technology generation (e.g., 200 kHz channels for 2G GSM).
- **Hierarchy**: 
  - `CellTower` (Base Class) → defines bandwidth and channel properties
  - `ThreadedCellTower` (Derived) → adds multi-threading support
  - `ThreadedTower2G/3G/4G/5G` (Specific Implementations) → generation-specific configurations

### 3. 🖥️ Cellular Core (`CellularCore.hpp`)
Represents the backend Core Network (CN).

- **Role**: Calculates the computational overhead and hardware requirements based on the traffic volume generated by users.
- **Logic**: Computes "Core Overhead" (per 100 messages) and "Cores Required" to process the signaling load generated by the users.
- **Use Case**: Primarily used in 4G (LTE) simulation to estimate Evolved Packet Core (EPC) requirements.


## 📶 Network Generation Concepts

The simulator implements distinct logic for each mobile generation to reflect real-world evolution:

| Generation | Concept Implemented | Technical Details                                                                                                                            |
| ---------- | ------------------- | -------------------------------------------------------------------------------------------------------------------------------------------- |
| 2G (GSM)   | FDMA / TDMA         | Uses narrow200 kHzchannels. Simulates basic voice capacity with lower user density per channel.                                              |
| 3G (UMTS)  | W-CDMA              | Uses wider5 MHzchannels. Allows higher user density and introduces data packet simulation.                                                   |
| 4G (LTE)   | OFDMA & EPC         | Focuses onCore Network Load. Calculates the overhead on the Evolved Packet Core (EPC) and requires CPU core estimation.                      |
| 5G (NR)    | Massive MIMO        | SimulatesMultiple Antennaarrays. Drastically increases capacity by using multiple antennas to serve users in parallel on the same frequency. |

## 🚀 Getting Started

Follow the instructions below for your operating system.

### 1️⃣ Prerequisites
- **C++ Compiler**: `g++` supporting C++17.
- **Make**: Standard build tool.
- **Terminal**: WSL (Ubuntu) for Windows or Terminal for macOS.

---

### 🐧 Windows (WSL) / Linux Instructions

For users running on **Windows Subsystem for Linux (WSL)** or native **Ubuntu/Debian**.

#### 🛠️ Build
Run the default make command from the root directory:
~~~text
make
~~~
This compiles the sim_debug executable using the standard syscall.s (x86_64 Linux ABI).

#### ▶️ Run
Execute the simulator:
~~~text
./sim_debug
~~~

### 🧹 Clean
To remove build artifacts:
~~~text
make clean
~~~

---

### 🍎 macOS Instructions

For users on **macOS** (Intel or Apple Silicon M1/M2/M3). The macOS system calls and assembly syntax differ from Linux, so we use the files in the `macos/` directory.

####🛠️ Build
1. Navigate to the `macos` folder from the project root:
~~~text
cd macos
~~~
2. Run the specific macOS Makefile:
~~~text
make
~~~
*This uses the macOS-compatible `syscall.s` and links correctly for Darwin systems.*

####▶️ Run
Run the generated executable:
~~~text
./sim_debug
~~~

#### 🧹 Clean
~~~text
make clean
~~~

---

## 🎮 How to Use

Once the simulator is running, you will see the main menu:
~~~text
+==========================================+
|      CELLULAR NETWORK SIMULATOR (MENU)   |
+==========================================+
| 1. Load Users from File                  |
+------------------------------------------+
| 2. Run 2G Simulation (GSM)               |
+------------------------------------------+
| 3. Run 3G Simulation (UMTS)              |
+------------------------------------------+
| 4. Run 4G Simulation (LTE)               |
+------------------------------------------+
| 5. Run 5G Simulation (NR)                |
+------------------------------------------+
| 6. Run Full Simulation (All Generations) |
+------------------------------------------+
| 7. Exit                                  |
+==========================================+
Select Option: 

~~~

1)Load Users: Select Option 1 first. Enter users.txt when prompted to load sample user IDs.

2)Run Simulation: Choose any generation (2G-5G) to see capacity, bandwidth allocation, and threading analysis.

3)Full Simulation: Option 6 runs all checks sequentially.

### 📝 Sample Output
~~~text
+==========================================+
|             5G (NR) ANALYSIS             |
+------------------------------------------+
| Total Capacity (Users): 4800             |
+------------------------------------------+
+------------------------------------------+
| Mapping loaded users to frequency        |
| channels...                              |
+------------------------------------------+
| Simulation Result: Accepted 250 users.   |
| Dropped 0 users.                         |
+------------------------------------------+

--- BANDWIDTH ALLOCATION REPORT ---
Channel 1 (Antenna 1):
    Users: [50001] [50002] [50003] ...
~~~


---

## 🔧 Troubleshooting

- **`Clock skew detected` warning**:
  Run `touch *` to update file timestamps, then run `make clean` and `make` again.

- **`undefined reference to IO::readString`**:
  Ensure you are using the updated `Basicio.cpp` and `syscall.s` provided in the latest update, which includes the `sys_read` implementation.

- **Assembly errors on macOS**:
  Ensure you are building inside the `macos/` directory using its specific Makefile, as the root Makefile is configured for Linux ELF64 format.

---









