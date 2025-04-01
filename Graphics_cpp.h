#ifndef GRAPHICS_CPP
#define GRAPHICS_CPP

#include "Graphics.h"
#include <cmath>
#include <array>

constexpr double PI = 3.14159265358979323846;

const PPM& Graphics::applyFilter(PPM& image, const char* filter) { 

    unsigned int width = image.getWidth();
    unsigned int height = image.getHeight();
    unsigned int maxColor = image.getMaxColor();
    PPM temp = image;
    std::array<float, 9> matrix;
    float w;

    if (strcmp(filter, "blur") == 0) {
        w = 1.0f / 9.0f;
        matrix = { w, w, w, w, w, w, w, w, w };
    }
    else if (strcmp(filter, "sharpen") == 0) {
        w = 1.0f / 3.0f;
        matrix = { 0, -w, 0, -w, (7 * w), -w, 0, -w, 0 };
    }
    else if (strcmp(filter, "edge") == 0) {
        matrix = { 0, 1, 0, 1, -4, 1, 0, 1, 0 };
    }
    else if (strcmp(filter, "emboss") == 0) {
        matrix = { -2, -1, 0, -1, 1, 1, 0, 1, 2 };
    }
    else if (strcmp(filter, "invert") == 0) {
        for (unsigned int y = 0; y < height; ++y) {
            for (unsigned int x = 0; x < width; ++x) {
                Pixel& p = image[y * width + x];
                p["red"] = maxColor - p["red"];
                p["green"] = maxColor - p["green"];
                p["blue"] = maxColor - p["blue"];
            }
        }
        return image;
    }
    else {
        std::cerr << "Unknown filter: " << filter << std::endl;
        return image;
    }

    for (unsigned int y = 1; y < height - 1; ++y) {
        for (unsigned int x = 1; x < width - 1; ++x) {
            int sumR = 0, sumG = 0, sumB = 0;
            unsigned int k = 0;

            for (int ky = -1; ky <= 1; ++ky) {
                for (int kx = -1; kx <= 1; ++kx) {
                    const Pixel& p = temp[(y + ky) * width + (x + kx)];
                    float weight = matrix[k++];

                    sumR += weight * p["red"];
                    sumG += weight * p["green"];
                    sumB += weight * p["blue"];
                }
            }

            sumR = std::max(0, std::min(static_cast<int>(maxColor), sumR));
            sumG = std::max(0, std::min(static_cast<int>(maxColor), sumG));
            sumB = std::max(0, std::min(static_cast<int>(maxColor), sumB));

            image[y * width + x] = Pixel(sumR, sumG, sumB);
        }
    }

    return image;
}

const PPM& Graphics::makeGrayScale(PPM& image) {
	for (unsigned int i = 0; i < image.getSize(); ++i) {
		unsigned int average = (image[i]["red"] + image[i]["green"] + image[i]["blue"]) / 3;
        image[i]["red"] = average;
        image[i]["green"] = average;
        image[i]["blue"] = average;
	}
	return image;
}

const PPM& Graphics::rotateImage(PPM& image, double degrees) {

    // Rotation matrix:
    // [ cos Theta  -sin Theta ]
    // [ sin Theta   cos Theta ]

    unsigned int width = image.getWidth();
    unsigned int height = image.getHeight();
    int centerWidth = width / 2;
    int centerHeight = height / 2;
    double angle = degrees * PI / 180.0;
    double cosTheta = std::cos(angle);
    double sinTheta = std::sin(angle);
    PPM temp = image;

    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            int xTranslated = x - centerWidth;
            int yTranslated = y - centerHeight;

            int xRotated = static_cast<int>(std::round(xTranslated * cosTheta - yTranslated * sinTheta));
            int yRotated = static_cast<int>(std::round(xTranslated * sinTheta + yTranslated * cosTheta));

            int newX = xRotated + centerWidth;
            int newY = yRotated + centerHeight;

            if (newX >= 0 && newX < static_cast<int>(width) && newY >= 0 && newY < static_cast<int>(height)) {
                image[y * width + x] = temp[newY * width + newX];
            }
            else {
                image[y * width + x] = Pixel(0, 0, 0);
            }
        }
    }
    return image;
}


const PPM& Graphics::scaleImage(PPM& image, double scale) {
    if (scale <= 0.0) {
        std::cerr << "Error: Scale factor must be greater than zero.\n";
        return image;
    }

    unsigned int width = image.getWidth();
    unsigned int height = image.getHeight();
    int centerWidth = width / 2;
    int centerHeight = height / 2;
    PPM temp = image;

    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            int xTranslated = x - centerWidth;
            int yTranslated = y - centerHeight;

            int xScaled = static_cast<int>(std::round(xTranslated / scale));
            int yScaled = static_cast<int>(std::round(yTranslated / scale));

            int newX = xScaled + centerWidth;
            int newY = yScaled + centerHeight;

            if (newX >= 0 && newX < static_cast<int>(width) && newY >= 0 && newY < static_cast<int>(height)) {
                image[y * width + x] = temp[newY * width + newX];
            }
            else {
                image[y * width + x] = Pixel(0, 0, 0);
            }
        }
    }
    return image;
}

const PPM& Graphics::translateImage(PPM& image, int shiftX, int shiftY) {
    unsigned int width = image.getWidth();
    unsigned int height = image.getHeight();

    if (std::abs(shiftX) >= width || std::abs(shiftY) >= height) {
        for (unsigned int i = 0; i < image.getSize(); ++i) {
            image[i]["red"] = image[i]["green"] = image[i]["blue"] = 0;
        }
        return image;
    }

    PPM temp = image;

    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            int xTranslated = x - shiftX;
            int yTranslated = y + shiftY;

            if (xTranslated >= 0 && xTranslated < static_cast<int>(width) && yTranslated >= 0 && yTranslated < static_cast<int>(height)) {
                image[y * width + x] = temp[yTranslated * width + xTranslated];
            }
            else {
                image[y * width + x] = Pixel(0, 0, 0);
            }
        }
    }
    return image;
}

#endif