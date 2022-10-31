#version 330 core

layout(location=0)in vec3 aPos;
layout(location=1)in vec3 aNormal;
layout(location=2)in vec3 aColor;
layout(location=3)in vec2 aTex;

out vec3 color;
out vec2 texCoord;
out vec3 normal;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 cameraProjectionView;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;

void main()
{
    
    fragPos = vec3(model * translation * -rotation * scale * vec4(aPos,1.f));
    color=aColor;
    texCoord= mat2(0.0, -1.0, 1.0, 0.0) * aTex;
    normal=mat3(transpose(inverse(model)))*aNormal;
    
    gl_Position=cameraProjectionView*model*vec4(aPos,1.);
}