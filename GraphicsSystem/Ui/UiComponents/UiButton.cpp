#include <iostream>
#include "UiButton.h"

UiButton::UiButton(float x, float y, float width, float height, Color *color) {
    this->color = color;
    setPositionX(x);
    setPositionY(y);
    setWidth(width);
    setHeight(height);
    updateTransforms();
    type = UI_BUTTON;
}

UiButton::UiButton(float x, float y, float width, float height, Texture *texture) {
    this->texture = texture;
    setPositionX(x);
    setPositionY(y);
    setWidth(width);
    setHeight(height);
    updateTransforms();
    type = UI_BUTTON;
}

UiButton::UiButton(float x, float y, float width, float height, Color *color, char *name, Font *font) {
    this->color = color;
    setPositionX(x);
    setPositionY(y);
    setWidth(width);
    setHeight(height);
    updateTransforms();
    type = UI_TEXT_BUTTON;
    this->font = font;
    text = new UiText(name, x, y, width, height, font, 20, TEXT_CENTERED);
}

UiButton::UiButton(float x, float y, float width, float height, Texture *texture, char *name, Font *font) {
    this->texture = texture;
    setPositionX(x);
    setPositionY(y);
    setWidth(width);
    setHeight(height);
    updateTransforms();
    type = UI_TEXT_BUTTON;
    this->font = font;
    text = new UiText(name, x, y, width, height, font, width / height * 10, TEXT_CENTERED);
}

void UiButton::mouseButtonInput(int button, int action, int mods){
    if (button == mouseButton && action == GLFW_PRESS) {
        if (hover) {
            pressed = true;
            clicked = true;
        }
    } else {
        pressed = false;
    }
}

void UiButton::mousePositionInput(double x, double y,double flippedY){
    if (getRotationX() == 0.0f && getRotationY() == 0.0f && getRotationZ() == 0.0f) {
        if (radiusX > 0 || radiusY > 0 || radiusZ > 0 || radiusW > 0) {
            hover = false;
            float radius;
            float center1X;
            float center1Y;
            float center2X;
            float center2Y;
            if (radiusX > radiusY) {
                radius = radiusX;
            } else {
                radius = radiusY;
            }
            if (distance(getPositionX() + radiusX - x, getPositionY() + radiusX - y) <= radiusX) {
                hover = true;
            }
            if (x >= getPositionX() && x <= getPositionX() + radius &&
                y >= getPositionY() + radiusX && y <= getPositionY() + getHeight() - radiusY) {
                hover = true;
            }
            center1X = getPositionX() + radiusX;
            center1Y = getPositionY() + radiusX;
            if (radiusY > radiusZ) {
                radius = radiusY;
            } else {
                radius = radiusZ;
            }
            if (distance(getPositionX() + radiusY - x, getPositionY() + getHeight() - radiusY - y) <=
                radiusY) {
                hover = true;
            }
            if (x >= getPositionX() + radiusY && x <= getPositionX() + getWidth() - radiusZ &&
                y >= getPositionY() + getHeight() - radius &&
                y <= getPositionY() + getHeight()) {
                hover = true;
            }
            if (radiusZ > radiusW) {
                radius = radiusZ;
            } else {
                radius = radiusW;
            }
            if (distance(getPositionX() + getWidth() - radiusZ - x,
                         getPositionY() + getHeight() - radiusZ - y) <= radiusZ) {
                hover = true;
            }
            if (x >= getPositionX() + getWidth() - radius &&
                x <= getPositionX() + getWidth() && y >= getPositionY() + radiusW &&
                y <= getPositionY() + getHeight() - radiusZ) {
                hover = true;
            }
            center2X = getPositionX() + getWidth() - radiusZ;
            center2Y = getPositionY() + getHeight() - radiusZ;
            if (radiusW > radiusX) {
                radius = radiusW;
            } else {
                radius = radiusX;
            }
            if (distance(getPositionX() + getWidth() - radiusW - x, getPositionY() + radiusW - y) <=
                radiusW) {
                hover = true;
            }
            if (x >= getPositionX() + radiusX && x <= getPositionX() + getWidth() - radiusW &&
                y >= getPositionY() && y <= getPositionY() + radius) {
                hover = true;
            }
            if (x >= center1X && x <= center2X && y >= center1Y && y <= center2Y) {
                hover = true;
            }
        } else {
            hover = x >= getPositionX() && x <= getPositionX() + getWidth() &&
                    y >= getPositionY() && y <= getPositionY() + getHeight();
        }
        if (!hover)
            pressed = false;
    }
}

float UiButton::distance(float x1, float x2) {
    return sqrt(x1 * x1 + x2 * x2);
}

bool UiButton::isClicked() {
    if (clicked) {
        clicked = false;
        return true;
    }
    return false;
}

void UiButton::updateText() {
   /* text->setPositionX(getPositionX());
    text->getPositionY() = getPositionY();
    text->getWidth() = getWidth();
    text->getHeight() = getHeight();
    text->updateTransforms();;*/
}

void UiButton::render(WindowContainer *container) {
    container->buttonShader->bind();
    if (hoverColor != nullptr) {
        container->buttonShader->setUniform4f("hoverColor", hoverColor->getNormalizedDecimal().r,
                                              hoverColor->getNormalizedDecimal().g,
                                              hoverColor->getNormalizedDecimal().b,
                                              hoverColor->getNormalizedDecimal().a);
    }else{
        container->buttonShader->setUniform4f("hoverColor", 0, 0, 0 ,0);
    }
    if (clickColor != nullptr) {
        container->buttonShader->setUniform4f("pressedColor", clickColor->getNormalizedDecimal().r,
                                              clickColor->getNormalizedDecimal().g,
                                              clickColor->getNormalizedDecimal().b,
                                              clickColor->getNormalizedDecimal().a);
    }else{
        container->buttonShader->setUniform4f("pressedColor", 0, 0, 0 ,0);
    }
    if (color != nullptr) {
        container->buttonShader->setUniform4f("color", color->getNormalizedDecimal().r,
                                              color->getNormalizedDecimal().g,
                                              color->getNormalizedDecimal().b,
                                              color->getNormalizedDecimal().a);
    }else{
        container->buttonShader->setUniform4f("color", 0, 0, 0 ,0);
    }
    if (texture != nullptr) {
        texture->bind();
    }
    if(isVisible()){
        container->buttonShader->setUniformBool("isHovered", hover);
        container->buttonShader->setUniformBool("isPressed", pressed);
        container->buttonShader->setUniformBool("hasTexture", color == nullptr);
        container->buttonShader->setUniform4f("corners", radiusX, radiusY, radiusZ, radiusW);
        container->buttonShader->setUniform1f("smoothness", smoothness);
        container->buttonShader->setUniform1f("uiWidth", getWidth());
        container->buttonShader->setUniform1f("uiHeight", getHeight());
        container->buttonShader->setUniformMatrix4f("model",getModelMatrix()->getBuffer());
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
    if (shouldShowHitBox()) {
        container->hitBoxShader->bind();
        container->hitBoxShader->setUniformMatrix4f("model", getModelMatrix()->getBuffer());
        container->hitBoxShader->setUniform4f("color", hitBoxColor->getNormalizedDecimal().r,
                                              hitBoxColor->getNormalizedDecimal().g,
                                              hitBoxColor->getNormalizedDecimal().b,
                                              hitBoxColor->getNormalizedDecimal().a);
        glDrawArrays(GL_LINE_LOOP, 0, 4);
    }
}

float UiButton::map(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
