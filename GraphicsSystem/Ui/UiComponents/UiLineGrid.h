#pragma once

#include <Ui/UiElements/UiElement.h>
#include <Window/WindowContainer.h>

class ParticleManager;
class LineManager;

class UiLineGrid : public UiElement{
public:
    UiLineGrid();
    void render(WindowContainer* container);
    void update(double deltaTime);
    void mousePositionInput( double x, double y, double flippedY) override ;
private:
    LineManager* lineManager;
    ParticleManager* particleManager;
};
