#include "FileSystemSimulator.h"
#include <iostream>

int main() {
    try {
        FileSystemSimulator simulator;
        simulator.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
