#pragma once

#include "../UiElements/UiElement.h"
#include "../UiComponents/UiRectangle.h"
#include "../UiComponents/UiButton.h"
#include "../UiUtil/UiColor.h"
#include <Matrix/Matrix4f.h>
#include <vector>
#include "Window/WindowContainer.h"
#include "OpenGL.h"
#include "Shader.h"

class UiPanel : public UiRectangle{
public:
    UiPanel(float x, float y, float width, float height, Color* background);
    UiPanel();
    void addElement(UiElement* element);
    void render(WindowContainer* container) override;
    void updateTransforms() override;
    inline void setBackgroundColor(Color* color){this->background = color;}
    inline Color* getBackgroundColor(){return background;}
    void mouseButtonInput(int button, int action, int mods) override ;
    void mousePositionInput( double x, double y, double flippedY) override ;
    void mouseWheelInput(double xOffset, double yOffset) override;
    inline std::vector<UiElement*>* getElements(){return &elements;}
private:
    Color* background = new Color("#333331");
    float map(float x, float in_min, float in_max, float out_min, float out_max);
    std::vector<UiElement*> elements;
};

