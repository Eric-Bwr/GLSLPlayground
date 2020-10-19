#vertex
#version 400 core

layout (location = 0) in vec2 inPosition;

uniform mat4 model;
uniform mat4 ortho;

void main(){
    gl_Position =  ortho * model * vec4(inPosition, 0.0, 1.0);
}

    #fragment
    #version 400 core

uniform vec4 color;

out vec4 outColor;

void main() {
    outColor = color;
}