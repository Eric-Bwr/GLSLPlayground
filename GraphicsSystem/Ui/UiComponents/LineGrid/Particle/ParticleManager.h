#pragma once

#include "vector"
#include "Particle.h"
#include "Window/Window.h"

class LineManager;

class ParticleManager {
public:
    ParticleManager(LineManager* lineManager, float x, float y, float width, float height);
    void addParticles(int amount);
    void update(float delta);
    void render(WindowContainer* window);
    bool hitBox = true;
    std::vector<Particle*> particles;
    float distance(float x1, float x2);
    float map(float x, float in_min, float in_max, float out_min, float out_max);
    float posX, posY, width,height;
    void mousePositionInput(double x, double y);
    Color* hitBoxColor = new Color("#ffffff");
private:
    LineManager* lineManager;
    double mouseX, mouseY;
    Particle* cursor;
    Matrix4f model;
};
