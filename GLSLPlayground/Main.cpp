#include <chrono>
#include <iostream>
#include "Window/WindowSettings.h"
#include "Window/Window.h"
#include "Window/WindowManager.h"
#include "Buffer.h"

int main(){
    WindowSettings* windowSettings = new WindowSettings();
    windowSettings->setSize(1280,720);
    windowSettings->setLocation(0,0);
    windowSettings->setShouldAutoScale(false);
    windowSettings->setVersionMinor(3);
    windowSettings->setVersionMajor(3);
    windowSettings->setProfile(GLFW_OPENGL_CORE_PROFILE);
    windowSettings->setCheckVersion(true);
    windowSettings->setResizable(true);
    windowSettings->setCentered(true);
    windowSettings->setIcon((char*)"../Assets/Textures/WindowIcon");
    windowSettings->setWindowMode(WINDOW_MODE_BORDERLESS);
    windowSettings->setTitle((char*)"Window!");
    windowSettings->setShouldMultiSample(true);
    windowSettings->setSampleSize(4);
    windowSettings->setSwapInterval(1);
    WindowManager* manager = new WindowManager();
    Window* window = new Window(windowSettings);

    manager->addWindow(window);
    auto shader = window->windowContainer->shader;
    shader->bind();
    shader->setUniform2f("resolution",windowSettings->getWidth(),windowSettings->getHeight());
    std::cout << shader->getErrorMessage() << "\n";


    manager->sortUiElements();
    while(manager->hasWindows()){
        auto t_start = std::chrono::high_resolution_clock::now();


        shader->bind();
        shader->setUniform1f("time", glfwGetTime());
        window->windowContainer->vao->bind();
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        auto t_end = std::chrono::high_resolution_clock::now();
        double deltaTime = std::chrono::duration<double, std::milli>(t_end-t_start).count();
        deltaTime *= window->getMonitorInformation()->refreshRate;
        deltaTime /= 1000;
        manager->update();
    }
    glfwTerminate();
    manager->destroy();
}
