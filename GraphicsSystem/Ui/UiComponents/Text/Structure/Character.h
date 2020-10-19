#pragma once

class Character {

public:
    Character(float id, float x, float y, float width, float height, float xoffset, float yoffset, float xadvance);
    inline float getId() const {return id;}
    inline void setId(float id){this->id = id;}
    inline float getX() const {return x;};
    inline void setX(float x) {this->x = x;}
    inline float getY() const {return y;}
    inline void setY(float y) {this->y = y;};
    inline float getWidth() const {return width;}
    inline void setWidth(float width) {this->width = width;}
    inline float getHeight() const {return height;}
    inline void setHeight(float height)  {this->height = height;}
    inline float getXoffset() const {return xOffset;}
    inline void setXoffset(float xoffset)  {this->xOffset = xoffset;}
    inline float getYoffset() const {return yOffset;}
    inline void setYoffset(float yoffset)  {this->yOffset = yoffset;}
    inline float getXadvance() const {return xAdvance;}
    inline void setXadvance(float xadvance)  {this->xAdvance = xadvance;}
private:
    float id = 0.f,x = 0.f,y = 0.f,width = 0.f, height = 0.f, xOffset = 0.f,yOffset = 0.f,xAdvance = 0.f;
};