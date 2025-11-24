#include "Basicio.h"
#include "ThreadedTowers.hpp"
#include "UserDevice.hpp"
#include "MiniSTL.h"

// --- Global Data ---
Vector<UserDevice> loadedUsers;

// --- Helper Functions ---

// Manual string-to-int parser (replaces std::stoi)
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
    
    // Question: How many user devices can be supported?
    IO::print("Total Capacity (Users): ");
    IO::printInt(tower.calculateTotalCapacity());
    IO::printLine("");

    if (loadedUsers.empty()) {
        IO::printLine("No users loaded. Please load data first to see allocation.");
    } else {
        // Question: Identify users occupying specific frequency
        tower.simulateWithLoadedUsers(loadedUsers);
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

    // Question: Identify the number of cellular cores needed
    // Assuming 1 Core can handle 100,000 messages
    int msgsPerUser = 10; 
    long totalMessages = (long)capacity * msgsPerUser;
    int coreCapacity = 100000;
    int coresNeeded = (totalMessages / coreCapacity) + 1;

    IO::print("Total Potential Messages: ");
    IO::printInt(totalMessages);
    IO::printLine("");
    IO::print("Cellular Cores Required (to support full potential): ");
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
        IO::printLine("6. Exit");
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
            case 6: 
                running = false; 
                IO::printLine("Exiting...");
                break;
            default:
                IO::printLine("Invalid option. Try again.");
        }
    }
    return 0;
}