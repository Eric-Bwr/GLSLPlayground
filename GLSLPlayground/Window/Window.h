#pragma once

#include <Texture.h>
#include <GLFW/glfw3.h>
#include "WindowSettings.h"
#include "../Ui/UiElements/UiElement.h"
#include "../Ui/UiComponents/UiSlider.h"
#include "../Ui/UiComponents/UiButton.h"
#include "../Ui/UiComponents/UiPanel.h"
#include "WindowContainer.h"
#include "WindowCallback.h"
#include "../Ui/UiComponents/UiTextField.h"
#include "../Ui/UiComponents/UiHeader.h"

#define FAILED_TO_LOAD_ICON_DATA -1
#define FAILED_TO_LOCATE_ICON_DATA -2
#define FAILED_TO_ALLOCATE_ICON_DATA -3
#define FAILED_TO_GET_TEXTURE_TYPE -4
#define FAILED_INIT_GLFW -5
#define FAILED_INIT_GLAD -6
#define FAILED_INIT_WINDOW -7

class Window{
public:
    explicit Window(WindowSettings* windowSettings);
    ~Window();
    void updateWindow();
    void destroyWindow();
    inline bool windowIsAlive() const { return !windowShouldClose; }
    inline GLFWwindow* getWindow(){ return window; }
    inline char* getGLVersion(){ return glVersion; }
    inline int getErrorCode() const{ return errorCode; }
    void addElement(UiElement* element);
    void showHitBoxes(bool show) const;
    inline void setHitBoxColor(Color* hitBoxColor) { this->hitBoxColor = hitBoxColor; }
    inline WindowSettings* getWindowSettings() { return windowSettings; };
    WindowCallback* windowCallback;
    WindowContainer* windowContainer;
    std::vector<UiElement*>* elements;
    void setHeader(UiHeader* header) { this->header = header; }
    inline UiHeader* getHeader(){ return header; }
    inline UiRectangle* getBody(){ return body; }
    inline const GLFWvidmode* getMonitorInformation(){return vidmode;}
private:
    GLFWwindow* window;
    const GLFWvidmode *vidmode;
    WindowSettings* windowSettings;
    Color* hitBoxColor = nullptr;
    void initHints();
    void constructWindow();
    void setIcon();
    char* glVersion;
    bool windowShouldClose = false;
    int errorCode = 0;
    UiHeader* header;
    UiRectangle* body;
};