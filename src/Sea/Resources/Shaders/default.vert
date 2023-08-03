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

float sd_rounded_box(vec3 pos, float radius)
{
    vec2 q = abs(pos.xy) + radius;
    return min(max(q.x, q.y), 0.0) + length(max(q, 0.0)) - radius;
}

void main()
{
    vec4 pos =  vec4(aPos, 1.0);
    fragPos = vec3(model * pos);
    color = aColor;
    texCoords = aTex;
    normal = mat3(transpose(inverse(model))) * aNormal;

    gl_Position = cameraProjectionView * vec4(fragPos, 1.0);
}