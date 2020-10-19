#include "MasterRenderer.h"

WindowManager* manager;
double flippedYPos = 0.0;

MasterRenderer::MasterRenderer(WindowManager* windowManager){
    manager = windowManager;
}

void MasterRenderer::keyInput(GLFWwindow *window, int key, int scancode, int action, int mods) {
    for(auto element : *manager->getWindow(window)->elements) {
        if (element->type == UI_TEXT_FIELD) {
            ((UiTextField*)element)->keyInput(key, scancode, action, mods);
        }
    }
}

void MasterRenderer::charInput(GLFWwindow *window, unsigned int character) {
    for(auto element : *manager->getWindow(window)->elements) {
        if (element->type == UI_TEXT_FIELD) {
            ((UiTextField*)element)->charInput(character);
        }
    }
}

void MasterRenderer::mouseButtonInput(GLFWwindow *window, int button, int action, int mods) {
    for(auto element : *manager->getWindow(window)->elements) {
        element->mouseButtonInput(button,action,mods);
    }
}

void MasterRenderer::mousePositionInput(GLFWwindow *window, double x, double y) {
    flippedYPos = y;
    y = manager->getWindow(window)->getWindowSettings()->getHeight() - y;
    for(auto element : *manager->getWindow(window)->elements) {
        element->mousePositionInput(x,y,flippedYPos);
    }
}

void MasterRenderer::framebufferSizeInput(GLFWwindow* window, int width, int height) {
    glfwMakeContextCurrent(window);
    if(!manager->getWindow(window)->getWindowSettings()->shouldAutoScale()){
        manager->getWindow(window)->windowContainer->ortho.identity();
        manager->getWindow(window)->windowContainer->ortho.orthographic(0.0f, (float)width, 0.0f, (float)height, -1.0, 1.0f);
        manager->getWindow(window)->windowContainer->reload();
    }
    glViewport(0, 0, width, height);
}

void MasterRenderer::mouseWheelInput(GLFWwindow *window, double xOffset, double yOffset) {
    for(auto element : *manager->getWindow(window)->elements) {
        element->mouseWheelInput(xOffset,yOffset);
    }
}


void MasterRenderer::render(Window* window) {
    glfwMakeContextCurrent(window->getWindow());
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    renderList(window->elements, window->windowContainer);
}

WindowManager* MasterRenderer::getWindowManager() {
    return manager;
}

void MasterRenderer::renderList(std::vector<UiElement*>* elements, WindowContainer* container) {
    container->vao->bind();
    for(auto element : *elements){
        switch(element->type){
            case UI_RECTANGLE:{
                auto rectangle = ((UiRectangle*)element);
                rectangle->render(container);
                break;
            }
            case UI_IMAGE:{
                auto image = ((UiImage*)element);
                image->render(container);
                break;
            }
            case UI_BUTTON:{
                auto button ((UiButton*)element);
                button->render(container);
                break;
            }
            case UI_TEXT_BUTTON:{
                auto button ((UiButton*)element);
                button->render(container);
                break;
            }
            case UI_SLIDER:{
                auto slider = ((UiSlider*)element);
                slider->render(container);
                break;
            }
            case UI_PANEL:{
                auto panel = ((UiPanel*)element);
                panel->render(container);
                renderList(panel->getElements(),container);
                break;
            }
            case UI_TEXT:{
                auto text = ((UiText *) element);
                text->render(container);
                break;
            }
            case UI_TEXT_FIELD:{
                break;
            }
            case UI_HEADER:{
                auto header = ((UiHeader*)element);
                header->render(container);
                renderList(header->getElements(),container);
                break;
            }
            case UI_LINEGRID:{
                auto lineGrid = ((UiLineGrid*)element);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE);
                lineGrid->render(container);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                break;
            }
        }
    }
}

