#pragma once

#include <Matrix/Matrix4f.h>
#include <Shader.h>
#include "../Particle/Particle.h"

class UiLine {
public:
    UiLine(float x, float y, float x2, float y2,float width, float height);
    void update();
    void render(Shader* shader) const;
    float alpha = 0.0f;
    float x,y,x2,y2;
    void updateLine();
    float distance(float x1, float x2);
    float map(float x, float in_min, float in_max, float out_min, float out_max);
    float maxConnectionDistance = 200.0f;
    bool maxBrightness = false;
    bool kill = false;
    Particle* particle1 = nullptr;
    Particle* particle2 = nullptr;
    Color* lineColor = new Color();
    Matrix4f model;
    ~UiLine();
private:
    float width, height;
};