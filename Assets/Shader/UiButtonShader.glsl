#vertex
#version 400 core

layout (location = 0) in vec2 inPosition;

uniform mat4 model;
uniform mat4 ortho;

out vec2 textureCoords;

void main(){
    textureCoords = (inPosition + 1.0) / 2.0;
    gl_Position =  ortho * model * vec4(inPosition, 0.0, 1.0);
}

    #fragment
    #version 400 core

in vec2 textureCoords;

uniform vec4 corners;
uniform float smoothness;
uniform float uiWidth;
uniform float uiHeight;

uniform bool hasTexture;
uniform sampler2D image;
uniform vec4 color;
uniform vec4 hoverColor;
uniform vec4 pressedColor;
uniform bool isHovered;
uniform bool isPressed;

out vec4 outColor;

float roundCorners(float alpha, vec4 radii, vec2 position){
    float yMaxY = uiHeight - radii.y;
    float xMaxZ = uiWidth - radii.z;
    float yMaxZ = uiHeight - radii.z;
    float xMaxW = uiWidth - radii.w;
    if(position.x < radii.x && position.y < radii.x){
        alpha *= 1.0 - smoothstep(radii.x - smoothness, radii.x + smoothness, length(position - vec2(radii.x)));
    }else if(position.x < radii.y && position.y > yMaxY){
        alpha *= 1.0 - smoothstep(radii.y - smoothness, radii.y + smoothness, length(position - vec2(radii.y, yMaxY)));
    }else if(position.x > xMaxZ && position.y > yMaxZ){
        alpha *= 1.0 - smoothstep(radii.z - smoothness, radii.z + smoothness, length(position - vec2(xMaxZ, yMaxZ)));
    } else if(position.x > xMaxW && position.y < radii.w){
        alpha *= 1.0 - smoothstep(radii.w - smoothness, radii.w + smoothness, length(position - vec2(xMaxW, radii.w)));
    }
    return alpha;
}

void main() {
    vec2 pos = textureCoords * vec2(uiWidth, uiHeight);
    vec4 texel = color;
    if(hasTexture){
        texel = texture(image, textureCoords);
        if (texel.w < 0.9)
            discard;
    }
    if(isHovered)
        texel += hoverColor;
    if(isPressed)
        texel += pressedColor;
    outColor = vec4(vec3(texel), texel.w * roundCorners(1.0f, corners, pos));
}