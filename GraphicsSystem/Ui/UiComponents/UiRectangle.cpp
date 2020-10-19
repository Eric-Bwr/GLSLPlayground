#include <iostream>
#include "UiRectangle.h"

UiRectangle::UiRectangle(float x, float y, float width, float height, float angle, Color *color) : color(color){
    setPositionX(x);
    setPositionY(y);
    setWidth(width);
    setHeight(height);
    setRotationZ(angle);
    type = UI_RECTANGLE;
}
UiRectangle::UiRectangle() {
    setPositionX(100);
    setPositionY(100);
    setWidth(100);
    setHeight(100);
    type = UI_RECTANGLE;
}


void UiRectangle::render(WindowContainer* container) {
    if(isVisible()){
        container->rectangleShader->bind();
        container->rectangleShader->setUniform4f("corners",getCornerBottomLeft(),getCornerTopLeft(),getCornerTopRight(),getCornerBottomRight());
        container->rectangleShader->setUniform1f("smoothness",getCornerSmoothness());
        container->rectangleShader->setUniform1f("uiWidth", getWidth());
        container->rectangleShader->setUniform1f("uiHeight", getHeight());
        container->rectangleShader->setUniform4f("color", getColor()->getNormalizedDecimal().r,getColor()->getNormalizedDecimal().g,getColor()->getNormalizedDecimal().b,getColor()->getNormalizedDecimal().a);
        container->rectangleShader->setUniformMatrix4f("model",getModelMatrix()->getBuffer());
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
    if(shouldShowHitBox()) {
        container->hitBoxShader->bind();
        container->hitBoxShader->setUniformMatrix4f("model", getModelMatrix()->getBuffer());
        container->hitBoxShader->setUniform4f("color", hitBoxColor->getNormalizedDecimal().r, hitBoxColor->getNormalizedDecimal().g,hitBoxColor->getNormalizedDecimal().b, hitBoxColor->getNormalizedDecimal().a);
        glDrawArrays(GL_LINE_LOOP, 0, 4);
    }
}

UiRectangle::~UiRectangle() {
    delete color;
}

