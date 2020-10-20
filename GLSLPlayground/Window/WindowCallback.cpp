#include <iostream>
#include "WindowCallback.h"
#include "Window.h"

Window* window;
bool showMouseCoords = false;
bool wireframe = true;

WindowCallback::WindowCallback(Window* windowObj) {
    window = windowObj;
    glfwMakeContextCurrent(window->getWindow());
    glfwSetKeyCallback(window->getWindow(), keyCallback);
    glfwSetCharCallback(window->getWindow(), charCallback);
    glfwSetMouseButtonCallback(window->getWindow(), mouseButtonCallback);
    glfwSetCursorPosCallback(window->getWindow(), mousePositionCallback);
    glfwSetScrollCallback(window->getWindow(), mouseWheelCallback);
    glfwSetFramebufferSizeCallback(window->getWindow(), framebufferSizeCallback);
    glfwSetWindowPosCallback(window->getWindow(), windowPosCallback);
    glfwSetDropCallback(window->getWindow(), dropCallback);
    glfwSetWindowFocusCallback(window->getWindow(), windowFocusCallback);
    glfwSetWindowMaximizeCallback(window->getWindow(), windowMaximizeCallback);
}

void WindowCallback::keyCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods){
    if(key == GLFW_KEY_M && action == GLFW_PRESS){
        showMouseCoords = !showMouseCoords;
    }
    if(key == GLFW_KEY_RIGHT_SHIFT && action == GLFW_PRESS){
        glfwMakeContextCurrent(glfwWindow);
        window->windowContainer->shader->unbind();
        window->windowContainer->shader->reload();
        std::cout << window->windowContainer->shader->getErrorMessage() << "\n";
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
}

void WindowCallback::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods){
}

void WindowCallback::mousePositionCallback(GLFWwindow* window, double x, double y){

}

void WindowCallback::mouseWheelCallback(GLFWwindow* window, double xOffset, double yOffset){

}

void WindowCallback::framebufferSizeCallback(GLFWwindow* glfWwindow, int width, int height){
    glfwMakeContextCurrent(glfWwindow);
    glViewport(0, 0, width, height);
}

void WindowCallback::windowPosCallback(GLFWwindow* window, int x, int y){

}

void WindowCallback::dropCallback(GLFWwindow* window, int pathCount, const char* paths[]){

}

void WindowCallback::windowFocusCallback(GLFWwindow* window, int focused){

}

void WindowCallback::windowMaximizeCallback(GLFWwindow* window, int maximized){

}