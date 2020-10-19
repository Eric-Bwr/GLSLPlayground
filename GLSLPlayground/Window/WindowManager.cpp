#include <algorithm>
#include "WindowManager.h"
#include "../Renderer/MasterRenderer.h"

WindowManager::WindowManager(){
    MasterRenderer(this);
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
        MasterRenderer::render(window);
    }
}

void WindowManager::sortUiElements() {
    for(Window* window : windows){
       std::sort(window->elements->begin(),window->elements->end(),[](UiElement* a,UiElement* b){
            return a->getOrder() < b->getOrder();
       });
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
        window->showHitBoxes(show);
    }
}

bool WindowManager::hasWindows() {
    return !windows.empty();
}