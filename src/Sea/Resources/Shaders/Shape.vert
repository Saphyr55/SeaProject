#version 450 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec3 aColor;
layout(location = 3) in vec2 aTex;

uniform mat4 model;
uniform mat4 projectionView;

out vec2 position;
out vec3 color;

void main()
{   
    vec4 pos = vec4(aPos, 1.0);
    position = vec3(model * pos).xy; 
    color = aColor;

    gl_Position = projectionView * model * pos;
}