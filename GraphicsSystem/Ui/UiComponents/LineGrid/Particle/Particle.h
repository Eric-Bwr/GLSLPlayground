#pragma once

#include "Ui/UiComponents/UiRectangle.h"

class UiLine;

class Particle {
public:
    Particle(float boundingX, float boundingY, float boundingWidth, float boundingHeight, float x, float y, float size, float startDirectionX, float startDirectionY, float speed, float alpha, Color* color);
    void update(float delta);
    UiRectangle* rect;
    ~Particle();
    float size = 0;
private:
    float directionX = -2, directionY = -2;
    float alpha = 0, speed;
    float boundingX, boundingY, boundingWidth, boundingHeight;
    Color* color;
};