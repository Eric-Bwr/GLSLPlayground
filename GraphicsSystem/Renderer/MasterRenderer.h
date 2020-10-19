#pragma once

#include "../Ui/UiElements/UiElement.h"
#include "../Ui/UiComponents/UiRectangle.h"
#include "../Ui/UiComponents/UiImage.h"
#include "../Ui/UiComponents/UiButton.h"
#include "../Ui/UiComponents/UiText.h"
#include "../Ui/UiComponents/UiTextField.h"
#include "../Ui/UiComponents/UiSlider.h"
#include "../Ui/UiComponents/UiPanel.h"
#include <Matrix/Matrix4f.h>
#include <Shader.h>
#include <Buffer.h>
#include "Window/WindowManager.h"
#include "Windows.h"

class MasterRenderer{
public:
    explicit MasterRenderer(WindowManager* windowManager);
    static void keyInput(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void charInput(GLFWwindow* window,unsigned int character);
    static void mouseButtonInput(GLFWwindow* window, int button, int action, int mods);
    static void mousePositionInput(GLFWwindow* window, double x, double y);
    static void framebufferSizeInput(GLFWwindow* window, int width, int height);
    static void mouseWheelInput(GLFWwindow* window, double xOffset, double yOffset);
    static void render(Window* window);
    static WindowManager* getWindowManager();
    static void renderList(std::vector<UiElement*>* elements,WindowContainer* container);
};
