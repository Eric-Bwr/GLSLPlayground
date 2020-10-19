#include "UiLineGrid.h"
#include "LineGrid/Particle/ParticleManager.h"
#include "LineGrid/Line/LineManager.h"

UiLineGrid::UiLineGrid() {
    type = UI_LINEGRID;



     lineManager = new LineManager(500,500);



    particleManager = new ParticleManager(lineManager,50, 50, 400,400);
    particleManager->addParticles(40);
    lineManager->lineWidth = 2;
}

void UiLineGrid::render(WindowContainer* container) {
    lineManager->render(container);
    particleManager->render(container);
}

void UiLineGrid::update(double deltaTime) {
    particleManager->update(deltaTime);
}

void UiLineGrid::mousePositionInput(double x, double y, double flippedY) {
    particleManager->mousePositionInput(x,y);
}
