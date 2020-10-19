#pragma once

#include "UiText.h"
#include "UiRectangle.h"

class UiTextField : public UiElement {
public:
    UiTextField(char* text, float x, float y, float width, float height, Font* font, float fontSize, int textPosition = TEXT_VERTICAL_CENTERED);
    UiTextField(char* text, float x, float y, float width, float height, Font* font, float fontSize, Color* textColor, Color* outlineColor, int textPosition = TEXT_VERTICAL_CENTERED);
    UiTextField(char* text, float x, float y, float width, float height, Font* font, float fontSize, Texture* texture, Color *textColor, Color* outlineColor, int textPosition = TEXT_VERTICAL_CENTERED);
    void mouseButtonInput(int button, int action, int mods);
    void mousePositionInput(double x, double y);
    void charInput(unsigned int character);
    void keyInput(int key, int scancode, int action, int mods);
private:
    bool isHovered = false;
    bool isPressed = false;
    float cursor;
    UiText* text;
    UiRectangle* body;
};