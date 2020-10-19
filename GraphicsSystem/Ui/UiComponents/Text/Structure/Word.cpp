#include "Word.h"

Word::Word(float baseFontSize, float fontSize) {
    this->fontSize = fontSize;
    this->baseFontSize = baseFontSize;
}

void Word::addCharacter(Character *character) {
    characters.emplace_back(character);
    wordWidth += (character->getXadvance() / baseFontSize) * fontSize;
}

