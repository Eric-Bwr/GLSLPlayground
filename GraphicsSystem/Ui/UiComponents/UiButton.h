#pragma once

#include "../UiElements/UiElement.h"
#include "../UiUtil/UiColor.h"
#include <Matrix/Matrix4f.h>
#include <Texture.h>
#include "UiText.h"
#include "UiRectangle.h"
#include <GLFW/glfw3.h>

class UiButton : public UiElement {
public:
    UiButton(float x, float y, float width, float height, Color* color);
    UiButton(float x, float y, float width, float height, Texture* texture);
    UiButton(float x, float y, float width, float height, Color* color,char* name, Font* font);
    UiButton(float x, float y, float width, float height, Texture* texture,char* name, Font* font);
    inline Color* getColor() { return color; }

    inline void setMouseButton(unsigned int mouseButton) { this->mouseButton = mouseButton; }

    void mouseButtonInput(int button, int action, int mods) override;
    void mousePositionInput( double x, double y, double flippedY) override;

    bool isClicked();
    bool isPressed() const{ return pressed; }
    bool isHovered() const{ return hover; }
    inline void setHoverColor(Color* color){this->hoverColor = color;}
    inline void setClickColor(Color* color){this->clickColor = color;}
    inline UiRectangle* getBody() {return body; }
    inline Color* getHoverColor(){return hoverColor;}
    inline Color* getClickColor(){return clickColor;}
    inline Texture* getTexture(){return texture;}
    inline UiText* getText(){return text;}
    inline Font* getFont(){return font;}
    void updateText();
    inline void setRadius(float radiusX,float radiusY, float radiusZ, float radiusW){this->radiusX = radiusX; this->radiusY = radiusY; this->radiusZ = radiusZ; this->radiusW = radiusW;}
    float radiusX = 0.0f, radiusY = 0.0f, radiusZ = 0.0f, radiusW = 0.0f;
    float smoothness = 0.6;
    virtual void render(WindowContainer* container);
private:
    UiRectangle* body = nullptr;
    Color* color = nullptr;
    Texture* texture = nullptr;
    Font* font;
    Color* textColor;
    UiText* text = nullptr;
    bool hover = false, pressed = false, clicked = false;
    unsigned int mouseButton = GLFW_MOUSE_BUTTON_1;
    Color* hoverColor = nullptr;
    Color* clickColor = nullptr;
    float distance(float x1, float x2);
    float map(float x, float in_min, float in_max, float out_min, float out_max);
};