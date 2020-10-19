#pragma once

#include <string>

#define COLOR_DECIMAL 1
#define COLOR_NORMALIZED 2

struct color {
    float r; float g; float b; float a;
};

class Color{
public:
    Color();
    Color(float red, float green, float blue, float alpha, int colorMode);
    Color(const char* hex, float alpha = 1.0f);
    color getNormalizedDecimal() const;
    color getDecimal() const;
    std::string getHex();
    void setRGBA(float red, float green, float blue, float alpha, int colorMode);
    void setRed(float red,int colorMode);
    void setGreen(float green,int colorMode);
    void setBlue(float blue,int colorMode);
    void setAlpha(float alpha,int colorMode);
    ~Color();
private:
    float r = 0.0f, g = 0.0f, b = 0.0f, a = 1.0f;
};