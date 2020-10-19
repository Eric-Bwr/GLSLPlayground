#include "WindowCallback.h"

bool showMouseCoords = false;
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
    if(key == GLFW_KEY_M && action == GLFW_PRESS){
        showMouseCoords = !showMouseCoords;
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