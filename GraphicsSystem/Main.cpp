#include <Ui/UiComponents/UiRectangle.h>
#include <chrono>
#include "Window/WindowSettings.h"
#include "Window/Window.h"
#include "Window/WindowManager.h"
#include "Buffer.h"
#include "Ui/UiComponents/LineGrid/Line/UiLine.h"
#include "Ui/UiComponents/LineGrid/Line/LineManager.h"
#include "Ui/UiComponents/LineGrid/Particle/Particle.h"
#include "Ui/UiComponents/LineGrid/Particle/ParticleManager.h"


int main(){
    WindowSettings* windowSettings = new WindowSettings();
    windowSettings->setSize(500,500);
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
    windowSettings->setBackgroundColor(new Color("#222329"));
    windowSettings->setShouldMultiSample(true);
    windowSettings->setSampleSize(4);
    windowSettings->setSwapInterval(1);

    WindowManager* manager = new WindowManager();
    Window* window = new Window(windowSettings);

    manager->addWindow(window);

    UiPanel* panel = new UiPanel();
    UiPanel* panel2 = new UiPanel();

    panel->setConstraintX(50,PixelConstraint);
    panel->setConstraintY(50,PixelConstraint);
    panel->setConstraintWidth(50,PixelConstraint);
    panel->setConstraintHeight(80,PixelConstraint);

    panel2->setConstraintX(50,PixelConstraint);
    panel2->setConstraintY(50,PixelConstraint);
    panel2->setConstraintWidth(90,PixelConstraint);
    panel2->setConstraintHeight(90,PixelConstraint);

    //window->addElement(panel);

    UiButton* button = new UiButton(10,10,200,50,new Color("#4287f5"));

    UiSlider* slider = new UiSlider(0,0,100,20,SLIDER_HORIZONTAL,0,100,50);

    slider->setConstraintX(50,PixelConstraint);
    slider->setConstraintY(30,PixelConstraint);

    button->setHoverColor(new Color("ffffff"));

    button->setRadius(10,10,10,10);


    button->setConstraintX(50,PixelConstraint);
    button->setConstraintY(50,PixelConstraint);

    //
    auto lineGrid = new UiLineGrid();
    lineGrid->setOrder(1);
    window->addElement(lineGrid);
    panel2->setOrder(2);
   // panel2->addElement(button);nabend

   // panel2->addElement(slider);
   // panel->addElement(panel2);
    panel->setOrder(2);

    manager->sortUiElements();

    panel2->setBackgroundColor(new Color("#32a852"));

    //lineGrid->setConstraintX(50,PixelConstraint);

    //BUGS

    //TextRendering inside a Panel is fucking broken
    //font looks always bad just use down scaling

    while(manager->hasWindows()){
        auto t_start = std::chrono::high_resolution_clock::now();
        manager->update();
        manager->render();

        auto t_end = std::chrono::high_resolution_clock::now();
        double deltaTime = std::chrono::duration<double, std::milli>(t_end-t_start).count();
        deltaTime *= window->getMonitorInformation()->refreshRate;
        deltaTime /= 1000;
        lineGrid->update(deltaTime);

        if(button->isPressed()){
            std::cout << "pressed!\n";
        }
        if(glfwGetKey(window->getWindow(),GLFW_KEY_RIGHT) == GLFW_PRESS){
            panel->setPositionY(panel->getPositionY() + 1 * deltaTime);
        }

    }
    glfwTerminate();
    manager->destroy();
}
