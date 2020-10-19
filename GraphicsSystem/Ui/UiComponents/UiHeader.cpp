#include "UiHeader.h"
#include "UiSlider.h"
#include "UiPanel.h"

UiHeader::UiHeader(float x, float y, float width, float height, Color *color) : UiButton(x, y, width, height, color) {
    type = UI_HEADER;
    elements = new std::vector<UiElement*>;
}

void UiHeader::mouseButtonInput(int button, int action, int mods) {
    UiButton::mouseButtonInput(button, action, mods);
    for(auto element : *elements){
       element->mouseButtonInput(button,action,mods);
    }
    if(button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS){
        x = mouseX;
        y = mouseY;
        grab = true;
    }
    if(button == GLFW_MOUSE_BUTTON_1 && action == GLFW_RELEASE){
        grab = false;
        move = false;
    }
    if(point.y <= 1 && grab == false){
        glfwSetWindowPos(window, 0, 0);
        move = false;
        grab = false;
    }

}

void UiHeader::mousePositionInput(double xPos, double yPos, double flippedYPos) {
    UiButton::mousePositionInput(xPos, yPos,flippedYPos);
    for(auto element : *elements){
        element->mousePositionInput(xPos,yPos,flippedYPos);
    }
    if (isHovered()) {
        if (grab)
            move = true;
    }
    mouseX = xPos;
    mouseY = flippedYPos;
    if(move) {
        if (GetCursorPos(&point)){
            glfwSetWindowPos(window, point.x - (int) x, point.y - (int) y);
        }
    }
}

void UiHeader::addElement(UiElement *element) {
    elements->emplace_back(element);
    update();
}

void UiHeader::update() {
    UiButton::updateTransforms();
    for(UiElement* element : *elements){
        element->setAdditionalPadding(getPositionX(),getPositionY());
        element->updateConstraints(getWidth(),getHeight());
        element->updateTransforms();
        if(element->getPositionX()  + element->getWidth() - getPositionX() > getWidth() +1 || element->getPositionY() + element->getHeight() - getPositionY() > getHeight() +1){
            element->setVisibility(false);
            element->showHitBox(true);
        }
    }
}