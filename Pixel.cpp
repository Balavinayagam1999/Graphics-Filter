
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
    if(strcmp(i,"Red") == 0)
   {
     return r; 
   }
   else if(strcmp(i,"Green") == 0)
   {
     return g; 
   }
   else if(strcmp(i,"Blue") == 0)
   {
     return b; 
   }
   else
   {
    throw InputOutOfBoundsException("Not allowed", i); 
   }
    
};


unsigned int& Pixel::operator[](const char* i)
{
   if(strcmp(i,"Red") == 0)
   {
      return r;
   }
   else if(strcmp(i,"Green") == 0)
   {
     return g; 
   }
   else if(strcmp(i,"Blue") == 0)
   {
     return b; 
   }
   else
   {
    throw InputOutOfBoundsException("Not allowed", i); 
   }
   
};


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
