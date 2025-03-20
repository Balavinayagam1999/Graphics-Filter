#ifndef PPM_CPP
#define PPM_CPP

#include "PPM.h"
#include <iostream>


// Default Constructor
PPM::PPM() : width(0), height(0), maxColor(255), magic("P6") {}

// Copy Constructor
PPM::PPM(const PPM& other) : comment(other.comment), magic(other.magic), width(other.width), height(other.height), maxColor(other.maxColor), pixels(other.pixels) {}

// Move Constructor
PPM::PPM(PPM&& other) noexcept : comment(std::move(other.comment)), magic(std::move(other.magic)), width(other.width), height(other.height), maxColor(other.maxColor), pixels(std::move(other.pixels)) {}

// Constructor to Read from File !!! UNDERSTAND AND FIX THIS
PPM::PPM(std::ifstream& inputFile) {
    if (!inputFile) {
        std::cerr << "Error: Cannot open file.\n";
        return;
    }

    inputFile >> magic;
    if (magic != "P6") {
        std::cerr << "Error: Unsupported PPM format.\n";
        return;
    }

    inputFile >> width >> height >> maxColor;
    inputFile.ignore(); // Skip single whitespace after maxColor

    pixels.resize(width * height);
    inputFile.read(reinterpret_cast<char*>(pixels.data()), pixels.size() * sizeof(Pixel));
}

// Destructor !!! FINISH THIS
PPM::~PPM() {}

// Copy Assignment Operator
PPM& PPM::operator=(const PPM& other) {
    if (this != &other) {
        comment = other.comment;
        magic = other.magic;
        width = other.width;
        height = other.height;
        maxColor = other.maxColor;
        pixels = other.pixels;
    }
    return *this;
}

// Move Assignment Operator
PPM& PPM::operator=(PPM&& other) noexcept {
    if (this != &other) {
        comment = std::move(other.comment);
        magic = std::move(other.magic);
        width = other.width;
        height = other.height;
        maxColor = other.maxColor;
        pixels = std::move(other.pixels);
    }
    return *this;
}

// Getters
std::string PPM::getComment() const { return comment; }
std::string PPM::getMagic() const { return magic; }
unsigned int PPM::getWidth() const { return width; }
unsigned int PPM::getHeight() const { return height; }
unsigned int PPM::getMaxColor() const { return maxColor; }
unsigned int PPM::getSize() const { return width * height; }

// Setters
void PPM::setComment(std::string newComment) { comment = newComment; }
void PPM::setMagic(std::string newMagic) { magic = newMagic; }
void PPM::setWidth(unsigned int newWidth) { width = newWidth; pixels.resize(width * height); } // !!! UNDERSTAND AND FIX resize()
void PPM::setHeight(unsigned int newHeight) { height = newHeight; pixels.resize(width * height); } // !!! UNDERSTAND AND FIX resize()
void PPM::setMaxColor(unsigned int newMaxColor) { maxColor = newMaxColor; }

// Pixel Access Operators
const Pixel& PPM::operator[](unsigned int index) const {
    if (index >= pixels.size()) throw std::out_of_range("Index out of range");
    return pixels[index];
}

Pixel& PPM::operator[](unsigned int index) {
    if (index >= pixels.size()) throw std::out_of_range("Index out of range");
    return pixels[index];
}

// Resize Image !!! UNDERSTAND AND FIX resize()
void PPM::resize(unsigned int newSize) {
    pixels.resize(newSize);
}

// Save Image to File !!! UNDERSTAND AND FIX this
void PPM::saveImageToFile(std::string filename) const {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error: Cannot open file for writing.\n";
        return;
    }

    outFile << magic << "\n"
            << width << " " << height << "\n"
            << maxColor << "\n";

    outFile.write(reinterpret_cast<const char*>(pixels.data()), pixels.size() * sizeof(Pixel));
}

#endif