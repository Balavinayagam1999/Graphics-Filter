#include <iostream>
#include "PPM.h"
#include <fstream>

int main() {
    
    std::ifstream inputFile("test.txt");
    if (!inputFile) {
        std::cerr << "Failed to open text.txt\n";
        return 1;
    }

    PPM myPPM(inputFile);
    std::cout << myPPM.getSize() << std::endl;

    return 0;
}