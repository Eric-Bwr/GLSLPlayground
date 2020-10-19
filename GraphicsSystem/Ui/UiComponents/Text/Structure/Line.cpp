#include "Line.h"

void Line::addWord(Word *word) {
    words.emplace_back(word);
    currentLineLength += word->getWordWidth() + word->getSpaceWidth();
}
