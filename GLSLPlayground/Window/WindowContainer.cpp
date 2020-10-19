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
    shader = new Shader("../Assets/Shader/test.glsl");
    shader->bind();
    vao->bind();
}

void WindowContainer::reload() const {
    shader->bind();
    shader->setUniformMatrix4f("ortho",ortho.getBuffer());
}