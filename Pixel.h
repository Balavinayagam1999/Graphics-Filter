#ifndef PIXEL_H
#define PIXEL_H


class Pixel
{
private:


    unsigned int r, g, b;
public:
    // Constructors
    Pixel();
    Pixel(const Pixel&);
    Pixel(unsigned int, unsigned int, unsigned int);
    ~Pixel();
    const unsigned int& operator[](const char*) const;
    unsigned int& operator[](const char*);

};


#endif

