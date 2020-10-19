#pragma once

#include "../UiElements/UiTransform.h"
#include "../UiUtil/UiColor.h"
#include "Matrix/Matrix4f.h"
#include "../UiElements/UiElement.h"
#include "../UiComponents/UiButton.h"
#include "../UiComponents/UiLineGrid.h"
#include <Texture.h>
#include "Window/WindowContainer.h"
#include "OpenGL.h"
#include "Shader.h"

#define SLIDER_HORIZONTAL 0
#define SLIDER_VERTICAL 1

class UiSlider : public UiButton{
public:
    UiSlider(float x, float y, float width, float height, int direction, float start, float end, float defaultValue);
    void mouseButtonInput(int button, int action, int mods) override;
    void mousePositionInput( double x, double y, double flippedY) override;
    void mouseWheelInput(double xOffset, double yOffset) override;
    void updateSliderConstraints(float x, float y);
    void updateConstraints(float width, float height) override;
    inline UiButton* getThumb(){return thumb;}
    inline float getValue() const{return value;}
    void setValue(float value);
    void render(WindowContainer* container) override;
private:
    int direction = -1;
    float start = 0.0f;
    float end = 0.0f;
    float value = 0.0f;
    bool graped = false;
    double mouseX, mouseY;
    void calcValue();
    float map(float x, float in_min, float in_max, float out_min, float out_max);
    float previousValue;
    float mouseWheelSpeed = 5;
    UiButton* thumb;
};