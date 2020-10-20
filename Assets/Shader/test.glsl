#vertex
#version 400

layout (location = 0) in vec2 inPos;

void main(){
    gl_Position = vec4(inPos, 0.0, 1.0);
}

#fragment
#version 400

out vec4 outColor;

uniform vec2 resolution;
uniform float time;

#define Thickness 0.003

float drawLine(vec2 p1, vec2 p2) {
    vec2 uv = gl_FragCoord.xy / resolution.xy;
    float a = abs(distance(p1, uv));
    float b = abs(distance(p2, uv));
    float c = abs(distance(p1, p2));
    if ( a >= c || b >=  c ) return 0.0;
        float p = (a + b + c) * 0.5;
    float h = 2 / c * sqrt( p * ( p - a) * ( p - b) * ( p - c));
    return mix(1.0, 0.0, smoothstep(0.5 * Thickness, 1.5 * Thickness, h));
}

float circle(vec2 position, float radius){
    position.x -= sin(time) / 4;
    position.y -= tan(time) / 4;
return smoothstep(radius,length(position - vec2(0.5)), sin(time) /2);
}

float rectShape(vec2 position, vec2 center, vec2 sides) {

    float halfWidth = sides.x / 2.;
    float halfHeight = sides.y / 2.;
    vec2 shape = vec2(0.);

    shape.x = step(center.x - halfWidth, position.x) * step(position.x, center.x + halfWidth);
    shape.y = step(center.y - halfHeight, position.y) * step(position.y, center.y + halfHeight);

    return shape.x * shape.y;
}

void main(){
    vec2 fragPos = (gl_FragCoord.xy / resolution);

    float p = rectShape(fragPos,vec2(0.5),vec2(sin(time * 2) / 2 * 1));

    gl_FragColor = vec4(vec3(p),1.f);

}