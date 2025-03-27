#ifndef PIXEL_H
#define PIXEL_H


struct Pixel
{
private:


    unsigned char r, g, b;
public:
    // Constructors
    Pixel();
    Pixel(const Pixel&);
    Pixel(unsigned int, unsigned int, unsigned int);


    ~Pixel();
    const unsigned int& operator[](const char*) const;
    unsigned int& operator[](const char*);


    class InputOutOfBoundsException
    {
        private:
            const char* errorMessage;
            const char* offendingIndex;
        public:
            InputOutOfBoundsException(const char*err, const char* index): errorMessage(err), offendingIndex(index) {}
            const char* returnError() const
            {
                return errorMessage;
            }


            const char* returnOffendingIndex() const
            {
                return offendingIndex;
            }
    };  
};


#endif

