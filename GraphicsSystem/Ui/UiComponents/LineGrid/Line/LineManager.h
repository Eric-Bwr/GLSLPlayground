#pragma once

#include <Matrix/Matrix4f.h>
#include <Shader.h>
#include <Buffer.h>
#include <vector>
#include "UiLine.h"
#include "Window/Window.h"

class LineManager {
public:
    LineManager(float width, float height);
    void render(WindowContainer* window);
    VertexArrayObject* vao;
    VertexBufferObject* vbo;
    std::vector<UiLine*> lines;
    Matrix4f ortho;
    Shader* lineShader;
    float lineWidth = 3;
    ~LineManager();
};