#include "UiPanel.h"
#include "UiSlider.h"

UiPanel::UiPanel(float x, float y, float width, float height, Color* background) : UiRectangle(x,y,width,height,0.f,background){
    setPositionX(x);
    setPositionY(y);
    setWidth(width);
    setHeight(height);
    type = UI_PANEL;
    this->background = background;
}

UiPanel::UiPanel() : UiRectangle() {
    setPositionX(100);
    setPositionY(100);
    setWidth(100);
    setHeight(100);
    type = UI_PANEL;
}

void UiPanel::addElement(UiElement *element) {
    elements.emplace_back(element);
    updateTransforms();
}

void UiPanel::render(WindowContainer *container) {
    container->rectangleShader->bind();
    container->rectangleShader->setUniform4f("corners", getCornerBottomLeft(), getCornerTopLeft(), getCornerTopRight(), getCornerBottomRight());
    container->rectangleShader->setUniform1f("smoothness", getCornerSmoothness());
    container->rectangleShader->setUniform1f("uiWidth", getWidth());
    container->rectangleShader->setUniform1f("uiHeight", getHeight());
    container->rectangleShader->setUniform4f("color", background->getNormalizedDecimal().r, background->getNormalizedDecimal().g, background->getNormalizedDecimal().b, background->getNormalizedDecimal().a);
    container->rectangleShader->setUniformMatrix4f("model", getModelMatrix()->getBuffer());
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    if(shouldShowHitBox()) {
        container->hitBoxShader->bind();
        container->hitBoxShader->setUniformMatrix4f("model", getModelMatrix()->getBuffer());
        container->hitBoxShader->setUniform4f("color", hitBoxColor->getNormalizedDecimal().r, hitBoxColor->getNormalizedDecimal().g,hitBoxColor->getNormalizedDecimal().b, hitBoxColor->getNormalizedDecimal().a);
        glDrawArrays(GL_LINE_LOOP, 0, 4);
    }
}

void UiPanel::mousePositionInput(double x, double y, double flippedY) {
    UiRectangle::mousePositionInput(x,y,flippedY);
    x -= getPositionX();
    y -= getPositionY();
    for(auto element : elements){
        element->mousePositionInput(x,y,flippedY);
    }
}

void UiPanel::mouseButtonInput(int button, int action, int mods) {
    UiRectangle::mouseButtonInput(button,action,mods);
    for(auto element : elements){
        element->mouseButtonInput(button,action,mods);
    }
}

float UiPanel::map(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void UiPanel::updateTransforms() {
    UiTransform::updateTransforms();
    for(auto element : elements){
        element->setAdditionalPadding(getPositionX() + getAdditionalPaddingX() ,getPositionY() + getAdditionalPaddingY());
        element->updateConstraints(getWidth(),getHeight());
        element->updateTransforms();
        if(element->getPositionX()  + element->getWidth() > getWidth()  || element->getPositionY() + element->getHeight() > getHeight() ){
            element->setVisibility(false);
            element->showHitBox(true);
        }else{
            element->setVisibility(true);
            element->showHitBox(false);
        }
    }
}

void UiPanel::mouseWheelInput(double xOffset, double yOffset) {
    UiElement::mouseWheelInput(xOffset, yOffset);
    for(auto element : elements){
        element->mouseWheelInput(xOffset,yOffset);
    }
}


