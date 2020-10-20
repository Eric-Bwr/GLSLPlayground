#pragma once

#include <OpenGL.h>
#include <GLFW/glfw3.h>

class Window;

class WindowCallback{
public:
    explicit WindowCallback(Window* window);
private:
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void charCallback(GLFWwindow* window, unsigned int character);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void mousePositionCallback(GLFWwindow* window, double x, double y);
    static void mouseWheelCallback(GLFWwindow* window, double xOffset, double yOffset);
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void windowPosCallback(GLFWwindow* window, int x, int y);
    static void dropCallback(GLFWwindow* window, int pathCount, const char* paths[]);
    static void windowFocusCallback(GLFWwindow* window, int focused);
    static void windowMaximizeCallback(GLFWwindow* window, int maximized);
};