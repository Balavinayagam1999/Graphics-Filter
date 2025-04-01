#ifndef PIXEL_CPP
#define PIXEL_CPP

#include "Pixel.h"
#include <iostream>
#include <cstring>

using namespace std;


// Default Constructor
Pixel::Pixel() : red(0), green(0), blue(0) {};

// One parameter Constructor
Pixel::Pixel(const Pixel& T) : red(T.red), green(T.green), blue(T.blue) {};

// Three parameter Constructor
Pixel::Pixel(unsigned int Red, unsigned int Green, unsigned int Blue) : red(Red), green(Green), blue(Blue) {};

// Destructor
Pixel::~Pixel() {};

// Indexing Operator (const)
const unsigned int& Pixel::operator[](const char* i) const {
    if (strcmp(i, "red") == 0) return red;
    else if (strcmp(i, "green") == 0) return green;
    else if (strcmp(i, "blue") == 0) return blue;
    else {
        throw InputOutOfBoundsException("Invalid pixel component", i);
    }
}

// Indexing Operator 
unsigned int& Pixel::operator[](const char* i) {
    if (strcmp(i, "red") == 0) return red;
    else if (strcmp(i, "green") == 0) return green;
    else if (strcmp(i, "blue") == 0) return blue;
    else {
        throw InputOutOfBoundsException("Invalid pixel component", i);
    }
}


// InputOutOfBoundsException Class

// Constructor
Pixel::InputOutOfBoundsException::InputOutOfBoundsException(const char* err, const char* index)
    : errorMessage(err), offendingIndex(index) {}

// Return error message
const char* Pixel::InputOutOfBoundsException::returnError() const {
    return errorMessage;
}

// Return offending index
const char* Pixel::InputOutOfBoundsException::returnOffendingIndex() const {
    return offendingIndex;
}

#endif