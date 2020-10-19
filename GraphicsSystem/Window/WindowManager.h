#pragma once

#include "Window.h"
#include <vector>

class WindowManager{
public:
    WindowManager();
    void addWindow(Window* window);
    void removeWindow(Window* window);
    void update();
    void render();
    void sortUiElements();
    void destroy();
    inline std::vector<Window*> getWindows(){ return windows;}
    bool hasWindows();
    void showHitBoxes(bool show);
    Window* getWindow(GLFWwindow* glfwWindow);
private:
    std::vector<Window*> windows;
};