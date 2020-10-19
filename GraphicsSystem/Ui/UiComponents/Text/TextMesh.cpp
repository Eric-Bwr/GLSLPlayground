#include "TextMesh.h"

TextMesh::TextMesh() = default;

void TextMesh::load(GLFWwindow* window){
    this->window = window;
    glfwMakeContextCurrent(window);
    vao = new VertexArrayObject();
    layout = new VertexBufferObjectLayout();
    layout->pushFloat(2);
    layout->pushFloat(2);
    vbo = new VertexBufferObject(nullptr, 0, GL_DYNAMIC_DRAW);
    vao->addBuffer(*vbo, *layout);
}

void TextMesh::processText(char *text, float width, float height, Font *font, float fontSize, int textPosition) {
    vertices.clear();
    words.clear();
    lines.clear();
    processWords(text, font,fontSize);
    processLines(width);
    processVertices(width, height, textPosition, font,fontSize);
    vertexCount = vertices.size() / 4;
}

void TextMesh::reload(){
    glfwMakeContextCurrent(window);
    vbo->subData(vertices.data(), vertexCount * layout->getStride(), 0, GL_DYNAMIC_DRAW);
}

void TextMesh::processWords(char *text, Font *font, float fontSize) {
    Word* currentWord = new Word(font->getFontSize(), fontSize);
    Word* lastWord = nullptr;
    for (int i = 0; text[i] != '\0'; i++) {
        char currentChar = text[i];
        if(currentChar == ' '){
            if(currentWord != nullptr){
                if(currentWord->getCharacters().empty()){
                    currentWord->addStartSpace(font->getSpaceWidth() / font->getFontSize() * fontSize);
                }else{
                    currentWord->addSpace(font->getSpaceWidth() / font->getFontSize() * fontSize);
                }
            }
            if(currentWord->getCharacters().size() == 0){
                if(lastWord != nullptr){
                    lastWord->addSpace(font->getSpaceWidth() / font->getFontSize() * fontSize);
                }
            }else{
                words.emplace_back(currentWord);
                lastWord = currentWord;
                currentWord = new Word(font->getFontSize(), fontSize);
            }
        }else{
            currentWord->addCharacter(font->getCharacter(currentChar));
        }
    }
    words.emplace_back(currentWord);
    currentWord = nullptr;
}

void TextMesh::processLines(float width) {
    Line* currentLine = new Line();
    for(Word* word : words){
        if(word->getWordWidth() <= width){
            if(currentLine->getCurrentLineLength() + word->getWordWidth() + word->getSpaceWidth() <= width){
                currentLine->addWord(word);
            }else{
                lines.emplace_back(currentLine);
                currentLine = new Line();
                currentLine->addWord(word);
            }
        }
    }
    lines.emplace_back(currentLine);
    currentLine = nullptr;
}

void TextMesh::processVertices(float width, float height, int textPosition, Font *font, float fontSize) {
    float cursorX = 0.0f;
    float cursorY = height;
    Character* lastCharacter = nullptr;
    if(textPosition == TEXT_VERTICAL_CENTERED || textPosition == TEXT_CENTERED){
        cursorY = (height / 2 + (lines.size() * ((font->getHighestCharacter() / font->getFontSize()) * fontSize) )/ 2);
    }
    for(Line* line : lines){
        if(textPosition == TEXT_HORIZONTAL_CENTERED || textPosition == TEXT_CENTERED)
            if(!line->getWords().empty()) {
                cursorX = (width / 2 - (line->getCurrentLineLength() / 2) +
                           line->getWords().back()->getSpaceWidth() / 2);
            }
        for(Word* word : line->getWords()){
            if(cursorY - (font->getHighestCharacter() / font->getFontSize()) * fontSize  < 0.0f)
                break;
            cursorX += word->getStartSpace();
            for(Character* character : word->getCharacters()){
                if(lastCharacter != nullptr)
                    cursorX += lastCharacter->getXadvance() / font->getFontSize() * fontSize;
                lastCharacter = character;
                float characterHeight = (character->getHeight() / font->getFontSize()) * fontSize;
                float characterWidth = (character->getWidth() / font->getFontSize()) * fontSize;
                float characterYOffset = (character->getYoffset() / font->getFontSize()) * fontSize;
                float pixelMapped = 1.0f / font->getFontImageSize();
                float textureCoordX = pixelMapped * character->getX();
                float textureCoordY = pixelMapped * character->getY();
                float textureCoordSizeX = pixelMapped * (character->getX() + character->getWidth());
                float textureCoordSizeY = pixelMapped * (character->getY() + character->getHeight());
                float properX = map(cursorX,0,width,-1,1);
                float properY = map(cursorY + characterHeight - (characterYOffset +  characterHeight),0,height,-1,1);
                float properSizeX = map(cursorX + characterWidth,0,width,-1,1);
                float properSizeY = map(cursorY - (characterYOffset +  characterHeight),0,height,-1,1);
                vertices.emplace_back(properX);
                vertices.emplace_back(properSizeY);
                vertices.emplace_back(textureCoordX);
                vertices.emplace_back(textureCoordSizeY);
                vertices.emplace_back(properX);
                vertices.emplace_back(properY);
                vertices.emplace_back(textureCoordX);
                vertices.emplace_back(textureCoordY);
                vertices.emplace_back(properSizeX);
                vertices.emplace_back(properY);
                vertices.emplace_back(textureCoordSizeX);
                vertices.emplace_back(textureCoordY);
                vertices.emplace_back(properX);
                vertices.emplace_back(properSizeY);
                vertices.emplace_back(textureCoordX);
                vertices.emplace_back(textureCoordSizeY);
                vertices.emplace_back(properSizeX);
                vertices.emplace_back(properSizeY);
                vertices.emplace_back(textureCoordSizeX);
                vertices.emplace_back(textureCoordSizeY);
                vertices.emplace_back(properSizeX);
                vertices.emplace_back(properY);
                vertices.emplace_back(textureCoordSizeX);
                vertices.emplace_back(textureCoordY);
            }
            cursorX += word->getSpaceWidth();
        }
        cursorY -= (font->getHighestCharacter() / font->getFontSize()) * fontSize;
        cursorX = 0.0f;
        lastCharacter = nullptr;
    }
}

void TextMesh::render() {
    vao->bind();
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

float TextMesh::map(float x, float inMin, float inMax, float outMin, float outMax) {
    return (x - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}

bool TextMesh::canReload() {
    return window == nullptr;
}