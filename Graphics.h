#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "PPM.h"

class Graphics {
public:
	static const PPM& applyFilter(PPM&, const char*);
	static const PPM& makeGrayScale(PPM&);
	static const PPM& rotateImage(PPM&, double);
	static const PPM& scaleImage(PPM&, double);
	static const PPM& translateImage(PPM&, int, int);
};

#include "Graphics_cpp.h"
#endif
