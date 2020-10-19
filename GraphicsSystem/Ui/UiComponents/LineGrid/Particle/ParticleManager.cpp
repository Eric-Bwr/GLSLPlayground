#include <algorithm>
#include "ParticleManager.h"
#include "../Line/LineManager.h"

ParticleManager::ParticleManager(LineManager* lineManager, float x, float y, float width, float height) {
    this->lineManager = lineManager;
    this->width = width;
    this->height = height;
    this->posX = x;
    this->posY = y;
    cursor = new Particle(x,y,width,height,mouseX,mouseY,0,-1,-1,0,0,new Color("ffffff"));
    particles.emplace_back(cursor);
    model.identity();
    model.translate(x + (width / 2.0f), y + (height / 2.0f), 0);
    model.scale(width / 2.0f, height / 2.0f, 0.f);
}

void ParticleManager::addParticles(int amount){
    for(int i = 0; i < amount; i++){
        int directionX = rand() % 2;
        int directionY = rand() % 2;

        int x = (rand()%((int)width-(int)posX) + (int)posX);
        int y =(rand()%((int)height-(int)posY) + (int)posY);

        std::cout << x << std::endl;


        float speed  = (rand()%(600-200) + 200) /1000.0;
        float alpha  = (rand()%(900-200) + 200) /1000.0;
        auto color = new Color("#ffffff");
        color->setAlpha(alpha, COLOR_NORMALIZED);
        auto p = new Particle(posX,posY,width, height,x, y, 8, directionX, directionY, speed, alpha, color);
        particles.emplace_back(p);
    }
}

void ParticleManager::update(float delta) {
    for(Particle* p1 : particles){
        p1->update(delta);
        float pointX = p1->rect->getPositionX()+ p1->size / 2;
        float pointY = p1->rect->getPositionY() + p1->size / 2;

        if(distance(pointX - mouseX, pointY-mouseY) <= 180){
            for(UiLine* line : lineManager->lines){
                if(line->particle1 == p1 || line->particle2 == p1){
                    line->lineColor->setRGBA(255,0,0,100,COLOR_DECIMAL);
                    p1->rect->getColor()->setRGBA(255,0,0,100,COLOR_DECIMAL);
                    line->maxBrightness = true;
                }
            }
        }else{
            for(UiLine* line : lineManager->lines){
                if(line->particle1 == p1 || line->particle2 == p1){
                    line->lineColor->setRGBA(255,255,255,255,COLOR_DECIMAL);
                    p1->rect->getColor()->setRGBA(255,255,255,100,COLOR_DECIMAL);
                    line->maxBrightness = false;
                }
            }
        }

        for(Particle* p2 : particles){
            if(p2 == p1){
                continue;
            }
            float point1X = p1->rect->getPositionX() + p1->size / 2;
            float point1Y = p1->rect->getPositionY() + p1->size / 2;

            float point2X = p2->rect->getPositionX() + p2->size / 2;
            float point2Y = p2->rect->getPositionY() + p2->size / 2;

            float distanceValue = 200;


            float pointXCursor = cursor->rect->getPositionX() + cursor->rect->getWidth() / 2;
            float pointYCursor = cursor->rect->getPositionY() + cursor->rect->getHeight() / 2;

            if(distance(point2X - point1X, point2Y - point1Y) <= distanceValue ){
                bool shouldBreak = false;
                for(UiLine* line : lineManager->lines){
                    if(line->particle1 == p1 && line->particle2 == p2 || line->particle2 == p1 && line->particle1 == p2){
                        shouldBreak = true;
                        break;
                    }
                }
                if(!shouldBreak){
                        UiLine* line = new UiLine(point1X,point1Y,point2X,point2Y,500,500);
                        line->particle1 = p1;
                        line->particle2 = p2;
                        line->update();
                        lineManager->lines.emplace_back(line);
                       // p1->lineCount+=1;

                }


            }
        }
    }
    for (auto it = lineManager->lines.begin(); it != lineManager->lines.end(); ) {
        (*it)->updateLine();
        if( (*it)->kill) {
            delete * it;
            it = lineManager->lines.erase(it);
        }else {
            ++it;
        }
    }
}

void ParticleManager::render(WindowContainer* container) {
    for(Particle* p : particles){
        container->vao->bind();
        container->rectangleShader->bind();
        container->rectangleShader->setUniform4f("corners", p->rect->getCornerBottomLeft(), p->rect->getCornerTopLeft(),p->rect->getCornerTopRight(),p->rect->getCornerBottomRight());
        container->rectangleShader->setUniform1f("smoothness",p->rect->getCornerSmoothness());
        container->rectangleShader->setUniform1f("uiWidth", p->rect->getWidth());
        container->rectangleShader->setUniform1f("uiHeight",p->rect->getHeight());
        container->rectangleShader->setUniform4f("color", p->rect->getColor()->getNormalizedDecimal().r,p->rect->getColor()->getNormalizedDecimal().g,p->rect->getColor()->getNormalizedDecimal().b, p->rect->getColor()->getNormalizedDecimal().a);
        container->rectangleShader->setUniformMatrix4f("model",p->rect->getModelMatrix()->getBuffer());
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        if(hitBox) {
            container->hitBoxShader->bind();
            container->hitBoxShader->setUniformMatrix4f("model", model.getBuffer());
            container->hitBoxShader->setUniform4f("color", hitBoxColor->getNormalizedDecimal().r, hitBoxColor->getNormalizedDecimal().g, hitBoxColor->getNormalizedDecimal().b, hitBoxColor->getNormalizedDecimal().a);
            glDrawArrays(GL_LINE_LOOP, 0, 4);
        }
    }
}

float ParticleManager::distance(float x1, float x2) {
    return sqrt(x1 * x1 + x2 * x2);
}

float ParticleManager::map(float x, float in_min, float in_max, float out_min, float out_max) {
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void ParticleManager::mousePositionInput(double x, double y) {
    this->mouseX = x;
    this->mouseY = y;
    //cursor->rect->transform->positionX = mouseX;
    //cursor->rect->transform->positionY = mouseY;
    //cursor->rect->transform->update();
}