#pragma once

#include "Font.h"
#include "Structure/Line.h"
#include <Buffer.h>
#include <GLFW/glfw3.h>

#define TEXT_NORMAL 0
#define TEXT_HORIZONTAL_CENTERED 1
#define TEXT_VERTICAL_CENTERED 3
#define TEXT_CENTERED 4

class TextMesh{
public:
    TextMesh();
    void load(GLFWwindow* window);
    void processText(char* text,float width, float height, Font* font, float fontSize, int textPosition = 0);
    bool canReload();
    void reload();
    void render();
private:
    static float map(float x, float inMin, float inMax, float outMin, float outMax);
    void processWords(char* text, Font* font, float fontSize);
    void processLines(float width);
    void processVertices(float width, float height, int textPosition, Font* font, float fontSize);
    GLFWwindow* window;
    std::vector<float> vertices;
    std::vector<Word*> words;
    std::vector<Line*> lines;
    float spaceWidth = 30.f;
    VertexArrayObject* vao;
    VertexBufferObject* vbo;
    VertexBufferObjectLayout* layout;
    unsigned int vertexCount;
};