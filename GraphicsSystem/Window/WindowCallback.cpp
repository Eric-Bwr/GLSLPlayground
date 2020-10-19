#include "WindowCallback.h"

#include "../Renderer/MasterRenderer.h"

bool showHitBox = true;
bool showMouseCoords = false;
bool boxMode = false;
bool wireframe = true;

WindowCallback::WindowCallback(GLFWwindow* window) {
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetCharCallback(window, charCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, mousePositionCallback);
    glfwSetScrollCallback(window, mouseWheelCallback);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetWindowPosCallback(window, windowPosCallback);
    glfwSetDropCallback(window, dropCallback);
    glfwSetWindowFocusCallback(window, windowFocusCallback);
    glfwSetWindowMaximizeCallback(window, windowMaximizeCallback);
}

void WindowCallback::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    MasterRenderer::keyInput(window, key, scancode, action, mods);
    if(key == GLFW_KEY_H && action == GLFW_PRESS){
        showHitBox = !showHitBox;
        MasterRenderer::getWindowManager()->showHitBoxes(showHitBox);
    }
    if(key == GLFW_KEY_M && action == GLFW_PRESS){
        showMouseCoords = !showMouseCoords;
    }
    if(key == GLFW_KEY_B && action == GLFW_PRESS){
        boxMode = !boxMode;
        MasterRenderer::getWindowManager()->getWindow(window)->windowContainer->textShader->bind();
        MasterRenderer::getWindowManager()->getWindow(window)->windowContainer->textShader->setUniformBool("boxMode", boxMode);
    }
    if(key == GLFW_KEY_W && action == GLFW_PRESS){
        wireframe = !wireframe;
        if(wireframe){
            glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        }else{
            glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        }
    }
}

void WindowCallback::charCallback(GLFWwindow* window, unsigned int character){
    MasterRenderer::charInput(window, character);
}

void WindowCallback::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods){
    MasterRenderer::mouseButtonInput(window, button,action,mods);
}

void WindowCallback::mousePositionCallback(GLFWwindow* window, double x, double y){
    MasterRenderer::mousePositionInput(window, x, y);
    if(showMouseCoords)
        std::cout << "X: " << x << " | Y: " << y  << std::endl;
}

void WindowCallback::mouseWheelCallback(GLFWwindow* window, double xOffset, double yOffset){
    MasterRenderer::mouseWheelInput(window, xOffset, yOffset);
}

void WindowCallback::framebufferSizeCallback(GLFWwindow* glfWwindow, int width, int height){
    MasterRenderer::framebufferSizeInput(glfWwindow, width, height);
    auto window = MasterRenderer::getWindowManager()->getWindow(glfWwindow);
    height -= window->getHeader()->getHeight();
    for(UiElement* element : *window->elements){
        element->updateConstraints(width, height);
        if(element->type == UI_SLIDER){
            ((UiSlider*)element)->updateSliderConstraints(0, 0);
        }
        if(element->type == UI_TEXT_BUTTON){
            ((UiButton*)element)->updateText();
        }
    }
}

void WindowCallback::windowPosCallback(GLFWwindow* window, int x, int y){

}

void WindowCallback::dropCallback(GLFWwindow* window, int pathCount, const char* paths[]){

}

void WindowCallback::windowFocusCallback(GLFWwindow* window, int focused){

}

void WindowCallback::windowMaximizeCallback(GLFWwindow* window, int maximized){

}