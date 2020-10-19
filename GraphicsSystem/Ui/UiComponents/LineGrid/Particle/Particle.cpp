#include "Particle.h"

Particle::Particle(float boundingX, float boundingY, float boundingWidth, float boundingHeight, float x, float y, float size, float startDirectionX, float startDirectionY, float speed, float alpha, Color* color) {
    this->alpha = alpha;
    this->directionX = startDirectionX;
    this->directionY = startDirectionY;
    this->speed = speed;
    this->boundingX = boundingX;
    this->boundingY = boundingY;
    this->boundingWidth = boundingWidth;
    this->boundingHeight = boundingHeight;
    this->color = color;
    rect = new UiRectangle(x, y ,size, size,0.0f, color);
    rect->setRadius(size / 2.0f,size / 2.0f,size / 2.0f,size / 2.0f);
    this->size = size;
}

void Particle::update(float delta) {
    if(rect->getPositionX() + rect->getWidth() >= boundingX + boundingWidth){
        directionX = 0.0f;
    }
    if(rect->getPositionX() <= boundingX){
        directionX = 1.0f;
    }
    if(rect->getPositionY() + rect->getHeight() >= boundingY + boundingHeight){
        directionY = 0.0f;
    }
    if(rect->getPositionY() <= boundingY){
        directionY = 1.0f;
    }
    if(directionX == 1.0f){
        rect->setPositionX(rect->getPositionX()+speed * delta );
    }
    if(directionX == 0.0f){
        rect->setPositionX(rect->getPositionX()-speed * delta );
    }
    if(directionY == 1.0f){
        rect->setPositionY(rect->getPositionY()+speed * delta );
    }
    if(directionY == 0.0f){
        rect->setPositionY(rect->getPositionY()-speed * delta );
    }
}

Particle::~Particle() {
    delete rect;
    delete color;
}
