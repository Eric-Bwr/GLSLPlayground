#include <iostream>
#include "UiSlider.h"

UiSlider::UiSlider(float x, float y, float width, float height, int direction, float start, float end, float defaultValue) : UiButton(x,y,width,height,new Color("ffffff")) {
    setPositionX(x);
    setPositionY(y);
    setWidth(width);
    setHeight(height);
    type = UI_SLIDER;
    this->direction = direction;
    this->start = start;
    this->end = end;
    thumb = new UiButton(0,0,10,10,new Color("#fcba03"));
    thumb->setConstraintY(50,PixelConstraint);
    thumb->setConstraintHeight(100,PixelConstraint);
   /* if(direction == SLIDER_HORIZONTAL){
        thumbX = x ;
        thumbY = y;
        thumbWidth = 20;
        thumbHeight = height;
    }else{
        thumbX = x;
        thumbY = y + height / 2 - 10;
        thumbWidth = width;
        thumbHeight = 20;
    }*/
    this->value = defaultValue;
    previousValue = value;
    setValue(value);
}

void UiSlider::mousePositionInput(double x, double y, double flippedY) {
    UiButton::mousePositionInput(x,y,flippedY);
    x -= getPositionX();
    y -= getPositionY();
    mouseX = x;
    mouseY = y;
    thumb->mousePositionInput(x,y,flippedY);
    if(graped){
        if(direction == SLIDER_HORIZONTAL){
            thumb->setPositionX(mouseX - thumb->getWidth() / 2);
            if(mouseX + thumb->getWidth() / 2 > getWidth()){
                thumb->setConstraintX(100,PixelConstraint);
                thumb->updateConstraints(getWidth(),getHeight());

            }
            if(mouseX - thumb->getWidth() / 2 < 0){
                thumb->setConstraintX(0,PixelConstraint);
                thumb->updateConstraints(getWidth(),getHeight());
            }
        }
        calcValue();
    }
}

void UiSlider::mouseButtonInput(int button, int action, int mods) {
    UiButton::mouseButtonInput(button,action,mods);
    thumb->mouseButtonInput(button,action,mods);
    if(thumb->isPressed()){
        graped = true;
    }else{
        graped = false;
    }
    if(isPressed()){
        if(direction == SLIDER_HORIZONTAL){
            thumb->setPositionX(mouseX - thumb->getWidth() / 2);
            if(mouseX + thumb->getWidth() / 2 > getWidth()){
                thumb->setConstraintX(100,PixelConstraint);
                thumb->updateConstraints(getWidth(),getHeight());
            }
            if(mouseX - thumb->getWidth() / 2 < 0){
                thumb->setConstraintX(0,PixelConstraint);
                thumb->updateConstraints(getWidth(),getHeight());
            }
            calcValue();
            graped = true;
        }
    }
}

void UiSlider::mouseWheelInput(double xOffset, double yOffset) {
    if(isHovered()){
        if(direction == SLIDER_HORIZONTAL){
                if (yOffset == 1) {
                    if(thumb->getPositionX() + thumb->getWidth() < getWidth()){
                        thumb->setPositionX(thumb->getPositionX() + getWidth() / 100 * mouseWheelSpeed);
                    }else{
                        thumb->setPositionX(getWidth() - thumb->getWidth());
                    }
                } else if (yOffset == -1) {
                    if(thumb->getPositionX() > 0){
                        thumb->setPositionX(thumb->getPositionX() - getWidth() / 100 * mouseWheelSpeed);
                    }else{
                        thumb->setPositionX(0);
                    }
                }
                calcValue();

        }
    }
    if(thumb->getPositionX() + thumb->getWidth() > getWidth()){
        thumb->setPositionX(getWidth() - thumb->getWidth());
    }
    if(thumb->getPositionX() < 0){
        thumb->setPositionX(0);
    }
}


float UiSlider::map(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void UiSlider::calcValue() {
    if(direction == SLIDER_HORIZONTAL){
        value = map(thumb->getPositionX() + thumb->getWidth() / 2, thumb->getWidth() / 2, getWidth() - thumb->getWidth() / 2,start,end);
    }else{
        //value = map(thumbY - getPositionY(),0,getHeight() - thumbHeight,start ,end);
    }
    if(value != previousValue){
        previousValue = value;
    }
}

void UiSlider::setValue(float value) {
    if(value > end){
        value = end;
    }
    if(value < start){
        value = start;
    }
    if(direction == SLIDER_HORIZONTAL){
        thumb->setConstraintX(map(previousValue,start,end,0,100 ),PixelConstraint);
    }else{

    }
    if(value > end){
        value = end;
    }
    if(value < start){
        value = start;
    }
}

void UiSlider::render(WindowContainer *container) {
    UiButton::render(container);
    thumb->render(container);
}

void UiSlider::updateSliderConstraints(float x, float y) {

}

void UiSlider::updateConstraints(float width, float height) {
    UiTransform::updateConstraints(width,height);
    thumb->updateConstraints(getWidth(),getHeight());
    thumb->setAdditionalPadding(getAdditionalPaddingX() + getPositionX(),getAdditionalPaddingY() + getPositionY());
    thumb->updateTransforms();
    setValue(previousValue);
}

