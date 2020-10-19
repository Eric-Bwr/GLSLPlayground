#pragma once

#include "Text/TextMesh.h"
#include "../UiElements/UiElement.h"
#include "Window/WindowContainer.h"
#include "OpenGL.h"
#include "Shader.h"

class UiText : public UiElement{
public:
    UiText(char* text, float x, float y, float width, float height, Font* font, float fontSize, int textPosition = TEXT_CENTERED);
    UiText(char* text, float x, float y, float width, float height, Font* font, float fontSize, Color* textColor, Color* outlineColor, int textPosition = TEXT_CENTERED);
    inline TextMesh* getTextMesh() const{return textMesh;}
    inline Color* getTextColor() const { return textColor;}
    inline Color* getOutlineColor() const { return outlineColor;}
    inline Font* getFont() const {return font;}
    void setText(char* text);
    inline float getCharacterWidth() const { return characterWidth; }
    inline void setCharacterWidth(float characterWidth) { this->characterWidth = characterWidth; }
    inline float getCharacterEdge() const { return characterEdge; }
    inline void setCharacterEdge(float characterEdge) { this->characterEdge = characterEdge; }
    inline void setOutline(bool hasOutline){ this->outline = hasOutline; }
    inline bool hasOutline() const { return outline; }
    inline float getOutlineWidth() const { return outlineBorderWidth; }
    inline void setOutlineWidth(float outlineBorderWidth) { this->outlineBorderWidth = outlineBorderWidth; }
    inline float getOutlineEdge() const { return outlineBorderEdge; }
    inline void setOutlineEdge(float outlineBorderEdge) { this->outlineBorderEdge = outlineBorderEdge; }
    void render(WindowContainer* container);
private:
    TextMesh* textMesh = nullptr;
    Color* textColor = nullptr;
    Color* outlineColor = nullptr;
    Font* font = nullptr;
    char* text;
    float x,y,width,height,fontSize;
    int textPosition;
    bool outline = false;
    float characterWidth = 0.5f, characterEdge = 0.1f, outlineBorderWidth = 0.5f, outlineBorderEdge = 0.6f;
};