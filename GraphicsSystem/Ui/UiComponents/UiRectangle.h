#pragma once

#include "../UiElements/UiElement.h"
#include "../UiUtil/UiColor.h"
#include <Matrix/Matrix4f.h>
#include "Shader.h"
#include "Window/WindowContainer.h"
#include <OpenGL.h>

class UiRectangle : public UiElement {
public:
    UiRectangle(float x, float y, float width, float height, float angle, Color* color);
    UiRectangle();
    inline Color* getColor() { return color; }
    inline void setRadius(float radiusX, float radiusY, float radiusZ, float radiusW) { this->radiusX = radiusX, this->radiusY = radiusY, this->radiusZ = radiusZ, this->radiusW = radiusW; }
    inline void setCornerBottomLeft(float radiusX){ this->radiusX = radiusX; }
    inline void setCornerTopLeft(float radiusY){ this->radiusY = radiusY; }
    inline void setCornerTopRight(float radiusZ){ this->radiusZ = radiusZ; }
    inline void setCornerBottomRight(float radiusW){ this->radiusW = radiusW; }
    inline void setCornerSmoothness(float smoothness){this->smoothness = smoothness;}
    inline float getCornerBottomLeft(){return radiusX;}
    inline float getCornerTopLeft(){return radiusY;}
    inline float getCornerTopRight(){return radiusZ;}
    inline float getCornerBottomRight(){return radiusW;}
    inline float getCornerSmoothness(){return smoothness;}
    virtual void render(WindowContainer* container);
    ~UiRectangle();
private:
    Color* color = new Color("#4f4f4f");
    float radiusX = 0.0f, radiusY = 0.0f, radiusZ = 0.0f, radiusW = 0.0f;
    float smoothness = 0.6;
};