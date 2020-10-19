#include "LineManager.h"

LineManager::LineManager(float width, float height) {
    float positions[4] = { 0, 0, width, height };
    auto layout = new VertexBufferObjectLayout();
    layout->pushFloat(2);
    vbo = new VertexBufferObject(positions, layout->getStride() * 2, GL_STATIC_DRAW);
    vao = new VertexArrayObject();
    vao->addBuffer(*vbo, *layout);
    delete layout;
    ortho.identity();
    ortho.orthographic(0, width, 0, height, -1.0f, 1.0f);
    lineShader = new Shader("../Assets/Shader/LineGrid/UiLineShader.glsl");
    lineShader->bind();
    lineShader->setUniformMatrix4f("ortho", ortho.getBuffer());
}

void LineManager::render(WindowContainer* container) {
    lineShader->bind();
    glLineWidth(lineWidth);
    vao->bind();
    for(UiLine* line : lines){
        if(line != nullptr){
            line->render(lineShader);
        }
    }
}

LineManager::~LineManager() {
    delete vao;
    delete vbo;
    delete lineShader;
    lines.clear();
}