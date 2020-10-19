#pragma once

#include "UiButton.h"
#include <vector>
#include <windows.h>

class UiHeader : public UiButton {
public:
    UiHeader(float x, float y, float width, float height, Color *color);
    void mouseButtonInput(int button, int action, int mods) override;
    void mousePositionInput( double x, double y, double flippedY) override;
    inline std::vector<UiElement*>* getElements(){return elements;}
    void addElement(UiElement* element);
    void update();
    GLFWwindow* window = nullptr;
private:
    bool grab = false, move = false;
    POINT point;
    double x = 0.0, y = 0.0, mouseX = 0.0, mouseY = 0.0;
    std::vector<UiElement*>* elements;
};
