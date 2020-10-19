#vertex
#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 inTexCoords;

out vec2 textureCoords;

uniform mat4 model;
uniform mat4 ortho;

void main(void) {
    gl_Position = ortho * model * vec4(position,0.f, 1.0);
    textureCoords = inTexCoords;
}
    #fragment
    #version 330 core

in vec2 textureCoords;

uniform vec3 textColor;
uniform sampler2D fontAtlas;
uniform float characterWidth = 0.51;
uniform float characterEdge = 0.02;

uniform float u_buffer = 0.02f;
uniform float u_gamma = 0.5f;

uniform bool hasOutline;
uniform float outlineBorderWidth;
uniform float outlineBorderEdge;
uniform vec3 outlineColor;

out vec4 outColor;

uniform bool boxMode = false;

void main(void) {
    float distance = 1.0 - texture(fontAtlas, textureCoords).a;
    float textTransparency = 1.0 - smoothstep(characterWidth, characterWidth + characterEdge, distance);
    if(hasOutline){
       float outlineTransparency = 1.0 - smoothstep(outlineBorderWidth, outlineBorderWidth + outlineBorderEdge, distance);
       float alpha = textTransparency + (1.0 - textTransparency) * outlineTransparency;
       vec3 color = mix(outlineColor, textColor, textTransparency / alpha);
       outColor = vec4(color, alpha);
    }else{
       outColor = vec4(textColor, textTransparency);
    }
    if(boxMode){
        outColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
    //float dist = texture2D(fontAtlas, textureCoords).r;
    //float alpha = smoothstep(u_buffer - u_gamma, u_buffer + u_gamma, dist);
    //gl_FragColor = vec4(textColor.rgb, alpha );
   // outColor = vec4(textColor,texture(fontAtlas,textureCoords).a);

}