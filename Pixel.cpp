
#include "Pixel.h"
#include <iostream>


using namespace std;


// Default Constructor


Pixel::Pixel() : r(0), g(0), b(0)
{
    cout << "Default Pixel Constructor" << endl;
};


// One parameter Constructor
Pixel::Pixel(const Pixel& T) : r(T.r), g(T.g), b(T.b)
{
    cout << "Copy Constructor" << endl;
};


Pixel::Pixel(unsigned int Red, unsigned int Green, unsigned int Blue) : r(Red), g(Green), b(Blue)
{
    cout << "Three Parameter Pixel Constructor" << endl;
};




Pixel::~Pixel()
{
    cout << "Pixel Destructor" << endl;
};


const unsigned int& Pixel::operator[](const char* i) const
{
   
};


unsigned int& Pixel::operator[](const char* i)
{
   
};


