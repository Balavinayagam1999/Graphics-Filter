#ifndef PIXEL_H
#define PIXEL_H

class Pixel
{
private:
    unsigned int red, green, blue;

public:
    Pixel();
    Pixel(const Pixel&);
    Pixel(unsigned int, unsigned int, unsigned int);
    ~Pixel();
    const unsigned int& operator[](const char*) const;
    unsigned int& operator[](const char*);

    // Index Error Class
    class InputOutOfBoundsException
    {
    private:
        const char* errorMessage;
        const char* offendingIndex;
    public:
        InputOutOfBoundsException(const char*, const char*);
        const char* returnError() const;
        const char* returnOffendingIndex() const;
    };  
};

#include "Pixel_cpp.h";
#endif

