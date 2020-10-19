#pragma once

#include <map>
#include <vector>
#include "Structure/Character.h"
#include <fstream>
#include <iostream>
#include <Texture.h>

class Font {
public:
    Font(char* path,char* texturePath);
    inline Texture* getAtlas(){return atlas;}
    inline float getSpaceWidth() const{return space_width;}
    inline float getHighestCharacter() const{return highestCharacter;}
    inline float getFontSize() const{return fontSize;}
    inline float getFontImageSize() const{return fontImageSize;}
    inline bool hasError() const { return failedToLoad; }
    std::string getErrorMessage();
    void read();
    Character* getCharacter(char key);
    std::map<char,Character*> characters;
private:
    char* path;
    float fontSize, fontImageSize;
    Texture* atlas = nullptr;
    float space_width;
    float highestCharacter = 0.f;
    bool failedToLoad = false;
};