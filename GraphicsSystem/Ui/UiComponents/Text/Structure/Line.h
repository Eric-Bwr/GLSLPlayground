#pragma once

#include <vector>
#include "Word.h"

class Line {
public:
    void addWord(Word* word);
    inline float getCurrentLineLength() const{ return currentLineLength;}
    inline std::vector<Word*> getWords(){ return words; }
private:
    float currentLineLength = 0.0f;
    std::vector<Word*> words;
};
