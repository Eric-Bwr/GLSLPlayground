#include <algorithm>
#include "WindowManager.h"

WindowManager::WindowManager() {
}

void WindowManager::addWindow(Window *window) {
    window->windowCallback = new WindowCallback(window->getWindow());
    window->windowContainer = new WindowContainer(window->getWindow(), window->getWindowSettings()->getWidth(), window->getWindowSettings()->getHeight());
    windows.emplace_back(window);
}

void WindowManager::removeWindow(Window *window) {
    for(int i = 0; i < windows.size(); i++){
        if(windows.at(i) == window){
            windows.erase(windows.begin() + i);
        }
    }
}

void WindowManager::update() {
    for(auto window : windows){
        if(!window->windowIsAlive()) {
            window->destroyWindow();
            removeWindow(window);
            delete window->windowCallback;
            delete window->windowContainer;
            delete window;
        }else{
            window->updateWindow();
        }
    }
}

void WindowManager::render() {
    for(auto window : windows){
    }
}

void WindowManager::sortUiElements() {
    for(Window* window : windows){

    }
}

void WindowManager::destroy() {
    for (auto window : windows) {
        window->destroyWindow();
        removeWindow(window);
        delete window->windowCallback;
        delete window->windowContainer;
        delete window;
    }
}

Window* WindowManager::getWindow(GLFWwindow* glfwWindow){
    for(auto window : windows){
        if(window->getWindow() == glfwWindow){
            return window;
        }
    }
    return nullptr;
}

void WindowManager::showHitBoxes(bool show){
    for(auto window : windows){
    }
}

bool WindowManager::hasWindows() {
    return !windows.empty();
}