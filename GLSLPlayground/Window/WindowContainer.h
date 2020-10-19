#pragma once

#include <Matrix/Matrix4f.h>
#include <Buffer.h>
#include <Shader.h>
#include <GLFW/glfw3.h>

class WindowContainer{
public:
    WindowContainer(GLFWwindow* window, float width, float height);
    void reload() const;
    Matrix4f ortho;
    VertexArrayObject* vao;
    VertexBufferObject* vbo;
    Shader* shader;
};
