#include "Basicio.h"
#include "ThreadedTowers.hpp"
#include "UserDevice.hpp"
#include "MiniSTL.h"

// --- Global Data ---
Vector<UserDevice> loadedUsers;

// --- Helper Functions ---

// Manual string-to-int parser
int parseInt(const char* str) {
    int val = 0;
    int i = 0;
    // Skip whitespace
    while (str[i] == ' ' || str[i] == '\t') i++;
    
    // Parse digits
    while (str[i] >= '0' && str[i] <= '9') {
        val = val * 10 + (str[i] - '0');
        i++;
    }
    return val;
}

// Function to load user IDs from a text file
void loadUsersFromFile() {
    IO::print("Enter filename (e.g., users.txt): ");
    char filename[64];
    long len = IO::readLine(filename, 64);
    
    // Remove newline if present
    if (len > 0 && filename[len-1] == '\n') filename[len-1] = '\0';

    int fd = IO::openFile(filename);
    if (fd < 0) {
        IO::printLine("Error: Could not open file.");
        return;
    }

    loadedUsers.clear();
    char buffer[64];
    IO::printLine("Loading users...");

    while (true) {
        long readLen = IO::readLine(fd, buffer, 64);
        if (readLen == 0) break; // End of File

        int id = parseInt(buffer);
        if (id > 0) {
            UserDevice u(id);
            loadedUsers.push_back(u);
        }
    }

    IO::closeFile(fd);
    IO::print("Successfully loaded ");
    IO::printInt((long)loadedUsers.size());
    IO::printLine(" users.");
}

// --- Simulation Runners ---

void run2G() {
    IO::printLine("\n=== 2G (GSM) ANALYSIS ===");
    ThreadedTower2G tower;
    IO::print("Total Capacity (Users): ");
    IO::printInt(tower.calculateTotalCapacity());
    IO::printLine("");

    if (!loadedUsers.empty()) {
        tower.simulateWithLoadedUsers(loadedUsers);
    } else {
        IO::printLine("No users loaded. Please load data first.");
    }
}

void run3G() {
    IO::printLine("\n=== 3G (UMTS) ANALYSIS ===");
    ThreadedTower3G tower;
    IO::print("Total Capacity (Users): ");
    IO::printInt(tower.calculateTotalCapacity());
    IO::printLine("");

    if (!loadedUsers.empty()) {
        tower.simulateWithLoadedUsers(loadedUsers);
    } else {
        IO::printLine("No users loaded.");
    }
}

void run4G() {
    IO::printLine("\n=== 4G (LTE) ANALYSIS ===");
    ThreadedTower4G tower;
    
    int capacity = tower.calculateTotalCapacity();
    IO::print("Total Capacity (Users): ");
    IO::printInt(capacity);
    IO::printLine("");

    // Core Calculation Logic
    int msgsPerUser = 10; 
    long totalMessages = (long)capacity * msgsPerUser;
    int coreCapacity = 100000;
    int coresNeeded = (totalMessages / coreCapacity) + 1;

    IO::print("Cellular Cores Required for Max Capacity: ");
    IO::printInt(coresNeeded);
    IO::printLine("");

    if (!loadedUsers.empty()) {
        tower.simulateWithLoadedUsers(loadedUsers);
    } else {
        IO::printLine("No users loaded.");
    }
}

void run5G() {
    IO::printLine("\n=== 5G (NR) ANALYSIS ===");
    ThreadedTower5G tower;
    IO::print("Total Capacity (Users): ");
    IO::printInt(tower.calculateTotalCapacity());
    IO::printLine("");

    if (!loadedUsers.empty()) {
        tower.simulateWithLoadedUsers(loadedUsers);
    } else {
        IO::printLine("No users loaded.");
    }
}

void runFullSimulation() {
    IO::printLine("\n==========================================");
    IO::printLine("   STARTING FULL NETWORK SIMULATION");
    IO::printLine("==========================================");
    
    if (loadedUsers.empty()) {
        IO::printLine("WARNING: No users loaded. Simulation will be empty.");
    }

    run2G();
    run3G();
    run4G();
    run5G();

    IO::printLine("\n==========================================");
    IO::printLine("   FULL SIMULATION COMPLETE");
    IO::printLine("==========================================");
}

// --- Main Entry Point ---

int main() {
    char buffer[32];
    bool running = true;

    while (running) {
        IO::printLine("\n==========================================");
        IO::printLine("   CELLULAR NETWORK SIMULATOR (MENU)");
        IO::printLine("==========================================");
        IO::printLine("1. Load Users from File");
        IO::printLine("2. Run 2G Simulation (GSM)");
        IO::printLine("3. Run 3G Simulation (UMTS)");
        IO::printLine("4. Run 4G Simulation (LTE)");
        IO::printLine("5. Run 5G Simulation (NR)");
        IO::printLine("6. Run Full Simulation (All Generations)");
        IO::printLine("7. Exit");
        IO::print("Select Option: ");

        long len = IO::readLine(buffer, 32);
        if (len <= 0) continue;

        int choice = parseInt(buffer);

        switch (choice) {
            case 1: loadUsersFromFile(); break;
            case 2: run2G(); break;
            case 3: run3G(); break;
            case 4: run4G(); break;
            case 5: run5G(); break;
            case 6: runFullSimulation(); break;
            case 7: 
                running = false; 
                IO::printLine("Exiting...");
                break;
            default:
                IO::printLine("Invalid option. Try again.");
        }
    }
    return 0;
}