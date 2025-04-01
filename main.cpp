#include <iostream>
#include "Graphics.h"
#include <fstream>

int main(int argc, char* argv[]) {
    std::string inputFileName = "test.ppm";

    if (argc >= 2) {
        inputFileName = argv[1];
    }
    else {
        std::cout << "No input file provided. Using default: " << inputFileName << "\n";
    }
    
    std::ifstream inputFile(inputFileName);
    if (!inputFile) {
        std::cerr << "Failed to open " << inputFileName << "\n";
        return 1;
    }

    PPM myPPM(inputFile);
    inputFile.close();

    Graphics::makeGrayScale(myPPM);
    Graphics::scaleImage(myPPM, 0.5);
    Graphics::rotateImage(myPPM, 45);
    Graphics::translateImage(myPPM, 100, 200);
    Graphics::applyFilter(myPPM, "invert");
    myPPM.saveImageToFile("result.ppm");

    return 0;
}