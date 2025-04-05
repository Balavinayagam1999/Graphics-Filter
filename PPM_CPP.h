#ifndef PPM_CPP
#define PPM_CPP

#include "PPM.h"
#include <iostream>
#include <sstream>


// Default Constructor
PPM::PPM() : width(0), height(0), maxColor(255), magic("P6"), comment("") {}

// Copy Constructor
PPM::PPM(const PPM& other) : comment(other.comment), magic(other.magic), width(other.width), height(other.height), maxColor(other.maxColor), pixels(other.pixels) {}

// Move Constructor
PPM::PPM(PPM&& other) noexcept : comment(std::move(other.comment)), magic(std::move(other.magic)), width(other.width), height(other.height), maxColor(other.maxColor), pixels(std::move(other.pixels)) {}

// Constructor to Read from File
PPM::PPM(std::ifstream& inputFile) {
    if (!inputFile) {
        std::cerr << "Error: Cannot open file.\n";
        std::exit(EXIT_FAILURE);
    }

    inputFile >> magic;

    if (magic != "P3") {
        std::cerr << "Error: Unsupported PPM format. This app works with P3 format.\n";
        std::exit(EXIT_FAILURE);
    }

    std::string temp;
    while (std::getline(inputFile, temp)) {
        if (temp.empty()) continue;
        if (temp[0] == '#') {
            comment += temp + "\n";
        }
        else {
            std::istringstream lineStream(temp);
            lineStream >> width >> height;
            break;
        }
    }

    std::getline(inputFile, temp);
    maxColor = static_cast<unsigned int>(stoi(temp));

    if (width <= 0 || height <= 0 || maxColor <= 0) {
        std::cerr << "Error: Bad input for width, height, or max color.\n";
        std::exit(EXIT_FAILURE);
    }


    inputFile.ignore();

    pixels.reserve(width * height);

    std::string r, g, b;
    unsigned int rInt, gInt, bInt;

    for (int i = 0; i < width * height; ++i) {
        if (inputFile >> r >> g >> b) {
            try
            {
                rInt = std::stoi(r, nullptr, 10);
                gInt = std::stoi(g, nullptr, 10);
                bInt = std::stoi(b, nullptr, 10);
            }
            catch (const std::exception&)
            {
                std::cerr << "Error: Corrupted color values in file.\n";
                std::exit(EXIT_FAILURE);
            }
            if (rInt <= maxColor && gInt <= maxColor && bInt <= maxColor) {
                pixels.emplace_back(rInt, gInt, bInt);
            }
            else {
                std::cerr << "Error: Color values out of range.\n";
                std::exit(EXIT_FAILURE);
            }
        }
        else {
            std::cerr << "Error: Failed to read pixel data.\n";
            std::exit(EXIT_FAILURE);
        }
    }
}

// Destructor
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
void PPM::setComment(std::string newComment) { 
    if (newComment.empty()) {
        std::cout << "Empty Comment received. No changes have been made.\n";
        return;
    }
    if (newComment[0] != '#') {
        newComment = "# " + newComment;
    }
    comment = newComment; 
}
void PPM::setMagic(std::string newMagic) { 
    if (newMagic != "P3" && newMagic != "P6") {
        std::cerr << "Error: Invalid magic number. Use \"P3\" or \"P6\".\n";
        return;
    }
    magic = newMagic; 
}
void PPM::setMaxColor(unsigned int newMaxColor) { 
    if (newMaxColor == 0) {
        std::cerr << "Error: maxColor cannot be \"0\".\n";
        return;
    }
    maxColor = newMaxColor; 
}
void PPM::setWidth(unsigned int newWidth) { 
    if (newWidth == 0) {
        std::cerr << "Error: Width cannot be \"0\".\n";
        return;
    }
    width = newWidth; 
    pixels.resize(width * height); 
} 
void PPM::setHeight(unsigned int newHeight) { 
    if (newHeight == 0) {
        std::cerr << "Error: Height cannot be \"0\".\n";
        return;
    }
    height = newHeight; 
    pixels.resize(width * height); 
}

// Pixel Access Operators
const Pixel& PPM::operator[](unsigned int index) const {
    if (index >= pixels.size()) throw std::out_of_range("Index out of range");
    return pixels[index];
}

Pixel& PPM::operator[](unsigned int index) {
    if (index >= pixels.size()) throw std::out_of_range("Index out of range");
    return pixels[index];
}

// Resize Image
void PPM::resize(unsigned int newSize) {
    pixels.resize(newSize);
}

// Save Image to File
void PPM::saveImageToFile(std::string filename) const {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error: Cannot open file for writing.\n";
        std::exit(EXIT_FAILURE);
    }

    outFile << magic << "\n";
    comment != "" ?
        outFile << comment << width << " " << height << "\n" << maxColor << "\n" :
        outFile << width << " " << height << "\n" << maxColor << "\n";

    for (unsigned int i = 0; i < pixels.size(); ++i) {
        outFile << pixels[i]["red"] << " " << pixels[i]["green"] << " " << pixels[i]["blue"] << " ";
        if ((i + 1) % width == 0) outFile << "\n";
    }

    std::cout << "Output saved to " << filename << "\n";
}

#endif
