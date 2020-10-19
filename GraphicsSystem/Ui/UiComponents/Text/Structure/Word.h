#pragma once

#include <vector>
#include "Character.h"

class Word{
public:
    Word(float baseFontSize, float fontSize);
    void addCharacter(Character* character);
    inline void addSpace(float width){ spaceWidth += width; }
    inline float getWordWidth() const{ return wordWidth; }
    inline float getSpaceWidth() const { return spaceWidth; }
    inline std::vector<Character*> getCharacters(){ return characters; }
    inline void addStartSpace(float space){startSpace+= space;}
    inline float getStartSpace(){return startSpace;}
private:
    std::vector<Character*> characters;
    float fontSize = 0.0f;
    float baseFontSize = 0.0f;
    float wordWidth = 0.0f, spaceWidth = 0.0f, startSpace = 0.0f;
};