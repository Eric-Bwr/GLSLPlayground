#pragma once

#include "../UiElements/UiElement.h"
#include <Texture.h>
#include <Matrix/Matrix4f.h>
#include "Window/WindowContainer.h"
#include "OpenGL.h"
#include "Shader.h"

class UiImage : public UiElement {
public:
    UiImage(float x, float y, float width, float height, float angle, Texture* texture);
    inline Texture* getTexture() { return texture; }
    inline void setRadius(float radiusX, float radiusY, float radiusZ, float radiusW) { this->radiusX = radiusX, this->radiusY = radiusY, this->radiusZ = radiusZ, this->radiusW = radiusW; }
    inline void setCornerBottomLeft(float radiusX){ this->radiusX = radiusX; }
    inline void setCornerTopLeft(float radiusY){ this->radiusY = radiusY; }
    inline void setCornerTopRight(float radiusZ){ this->radiusZ = radiusZ; }
    inline void setCornerBottomRight(float radiusW){ this->radiusW = radiusW; }
    inline void setCornerSmoothness(float smoothness){this->smoothness = smoothness;}
    inline float getCornerBottomLeft() const{return radiusX;}
    inline float getCornerTopLeft() const{return radiusY;}
    inline float getCornerTopRight() const{return radiusZ;}
    inline float getCornerBottomRight() const{return radiusW;}
    inline float getCornerSmoothness() const{return smoothness;}
    void render(WindowContainer* container);
private:
    Texture* texture = nullptr;
    float radiusX = 0.0f, radiusY = 0.0f, radiusZ = 0.0f, radiusW = 0.0f;
    float smoothness = 0.6;
};