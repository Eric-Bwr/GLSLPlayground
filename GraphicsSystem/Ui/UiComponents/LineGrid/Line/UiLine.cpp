#include "UiLine.h"

UiLine::UiLine(float x, float y, float x2, float y2,float width, float height) {
    this->x = x;
    this->y = y;
    this->x2 = x2;
    this->y2 = y2;
    update();
    this->width = width;
    this->height = height;
    lineColor->setRGBA(255, 255, 255, 255, COLOR_DECIMAL);
}

void UiLine::update() {
    model.identity();
    model.translate(x,y,0);
    model.scale(1.0f / width * (x2-x), 1.0f / height * (y2 -y ), 0.0f);
}

void UiLine::render(Shader* shader) const {
    shader->setUniformMatrix4f("model", model.getBuffer());
    if(maxBrightness){
        if(alpha >= 0.2){
            shader->setUniform4f("color", lineColor->getNormalizedDecimal().r, lineColor->getNormalizedDecimal().g, lineColor->getNormalizedDecimal().b, 0.4);
        }else{
            shader->setUniform4f("color", lineColor->getNormalizedDecimal().r, lineColor->getNormalizedDecimal().g, lineColor->getNormalizedDecimal().b, alpha);
        }
    } else{
        shader->setUniform4f("color", lineColor->getNormalizedDecimal().r, lineColor->getNormalizedDecimal().g, lineColor->getNormalizedDecimal().b, alpha);
    }
    glDrawArrays(GL_LINES, 0, 2);
}

void UiLine::updateLine() {
    if(particle1 != nullptr && particle2 != nullptr) {
        float point1X = particle1->rect->getPositionX() + particle1->rect->getWidth() / 2;
        float point1Y = particle1->rect->getPositionY() + particle1->rect->getHeight() / 2;

        float point2X = particle2->rect->getPositionX()  + particle2->rect->getWidth() / 2;
        float point2Y = particle2->rect->getPositionY()  + particle2->rect->getHeight() / 2;

        x = point1X;
        y = point1Y;
        x2 = point2X;
        y2 = point2Y;
        update();

        if (distance(point2X - point1X, point2Y - point1Y) <= maxConnectionDistance) {
            alpha = map(distance(point2X - point1X, point2Y - point1Y), 0, maxConnectionDistance/2.8, 0.8, 0.4);
        } else {
            kill = true;
        }
    }
}

float UiLine::distance(float x1, float x2) {
    return sqrt(x1 * x1 + x2 * x2);
}

float UiLine::map(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

UiLine::~UiLine() {
    delete lineColor;
}
