#version 450 core

layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 cameraProjectionView;

void main()
{   
    gl_Position = cameraProjectionView * model * vec4(aPos, 1.0);
}