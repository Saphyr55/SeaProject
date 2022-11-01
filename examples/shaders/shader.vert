#version 450 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec3 aColor;
layout(location = 3) in vec2 aTexs;

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
    texCoords = mat2(0.0, -1.0, 1.0, 0.0) * aTexs;
    normal = mat3(transpose(inverse(model))) * aNormal;
    
    gl_Position = cameraProjectionView  * vec4(aPos, 1.0);
}