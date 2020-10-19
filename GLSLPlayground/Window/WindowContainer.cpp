#include <iostream>
#include "WindowContainer.h"

WindowContainer::WindowContainer(GLFWwindow *window, float width, float height) {
    glfwMakeContextCurrent(window);
    float positions[16] = {-1, 1, -1, -1,
                          -1, -1, -1, 1,
                          1, 1, 1, 1,
                          1, -1, 1, -1};
    auto layout = new VertexBufferObjectLayout();
    layout->pushFloat(2);
    layout->pushFloat(2);
    vbo = new VertexBufferObject(positions, layout->getStride() * 8, GL_STATIC_DRAW);
    vao = new VertexArrayObject();
    vao->addBuffer(*vbo, *layout);
    delete layout;
    ortho.identity();
    ortho.orthographic(0.0f, width, 0.0f, height, -1.0f, 1.0f);
    rectangleShader = new Shader("../Assets/Shader/UiRectangleShader.glsl");
    rectangleShader->bind();
    rectangleShader->setUniformMatrix4f("ortho", ortho.getBuffer());
    vao->bind();
    imageShader = new Shader("../Assets/Shader/UiImageShader.glsl");
    imageShader->bind();
    imageShader->setUniformMatrix4f("ortho", ortho.getBuffer());
    vao->bind();
    buttonShader = new Shader("../Assets/Shader/UiButtonShader.glsl");
    buttonShader->bind();
    buttonShader->setUniformMatrix4f("ortho", ortho.getBuffer());
    vao->bind();
    textShader = new Shader("../Assets/Shader/UiTextShader.glsl");
    textShader->bind();
    textShader->setUniformMatrix4f("ortho", ortho.getBuffer());
    hitBoxShader = new Shader("../Assets/Shader/UiHitBoxShader.glsl");
    hitBoxShader->bind();
    hitBoxShader->setUniformMatrix4f("ortho", ortho.getBuffer());
    vao->bind();

    std::cout << textShader->getErrorMessage() << std::endl;
}

void WindowContainer::reload() const {
    rectangleShader->bind();
    rectangleShader->setUniformMatrix4f("ortho",ortho.getBuffer());
    imageShader->bind();
    imageShader->setUniformMatrix4f("ortho",ortho.getBuffer());
    buttonShader->bind();
    buttonShader->setUniformMatrix4f("ortho",ortho.getBuffer());
    textShader->bind();
    textShader->setUniformMatrix4f("ortho",ortho.getBuffer());
    hitBoxShader->bind();
    hitBoxShader->setUniformMatrix4f("ortho",ortho.getBuffer());
}