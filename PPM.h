#ifndef PPM_H
#define PPM_H

#include <vector>
#include <string>
#include <fstream>
#include "Pixel.h"

class PPM {
private:
    std::string comment;
    std::string magic;
    unsigned int width;
    unsigned int height;
    unsigned int maxColor;
    std::vector<Pixel> pixels;

public:

    // Constructors
    PPM();
    PPM(const PPM& other);
    PPM(PPM&& other) noexcept;
    PPM(std::ifstream& inputFile);

    // Destructor
    ~PPM();

    // Assignment operators
    PPM& operator=(const PPM& other);
    PPM& operator=(PPM&& other) noexcept;

    // Indexing Operators for accessing Pixels
    const Pixel& operator[](unsigned int index) const;
    Pixel& operator[](unsigned int index);
    
    // Getters
    std::string getComment() const;
    std::string getMagic() const;
    unsigned int getWidth() const;
    unsigned int getHeight() const;
    unsigned int getMaxColor() const;
    unsigned int getSize() const;

    // Setters
    void setComment(std::string comment);
    void setMagic(std::string magic);
    void setWidth(unsigned int width);
    void setHeight(unsigned int height);
    void setMaxColor(unsigned int maxColor);

    // Image manipulations
    void resize(unsigned int newSize);
    void saveImageToFile(std::string filename) const;
};

#include "PPM_cpp.h";

#endif