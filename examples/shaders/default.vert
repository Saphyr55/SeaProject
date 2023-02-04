#version 450 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec3 aColor;
layout(location = 3) in vec2 aTex;

out vec3 color; 
out vec2 texCoords;
out vec3 normal;
out vec3 fragPos;

uniform mat4 cameraProjectionView;
uniform mat4 model;

void main()
{
    fragPos = vec3(model * vec4(aPos, 1.0));
    color = aColor;
    texCoords = aTex;
    normal = mat3(transpose(inverse(model))) * aNormal;
    
    gl_Position = cameraProjectionView * model * vec4(aPos, 1.0);
}