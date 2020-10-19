#pragma once

#include "UiTransform.h"
#include "../UiUtil/UiColor.h"

#define UI_RECTANGLE 1
#define UI_IMAGE 2
#define UI_BUTTON 3
#define UI_TEXT_BUTTON 4
#define UI_TEXT 5
#define UI_TEXT_FIELD 6
#define UI_SLIDER 7
#define UI_PANEL 8
#define UI_HEADER 9
#define UI_LINEGRID 10

class UiElement : public UiTransform{
public:
    inline void setOrder(int order) { this->order = order; }
    inline int getOrder() const { return order; }
    inline void showHitBox(bool hitBox) { this->hitBox = hitBox; }
    inline bool shouldShowHitBox() const { return hitBox; }
    inline bool setVisibility(bool visible){this->visible = visible;}
    inline bool isVisible(){return visible;}
    virtual void mouseButtonInput(int button, int action, int mods);
    virtual void mousePositionInput(double x, double y, double flippedY);
    virtual void charInput(unsigned int character);
    virtual void keyInput(int key, int scancode, int action, int mods);
    virtual void mouseWheelInput(double xOffset, double yOffset);
    int type;
    Color* hitBoxColor = new Color("#ffffff");
private:
    bool hitBox = false;
    bool visible = true;
    int order = 0;
};

