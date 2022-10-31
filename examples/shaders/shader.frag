#version 330 core

out vec4 FragColor;

in vec3 fragPos;
in vec3 normal;
in vec3 color;
in vec2 texCoord;

uniform sampler2D diffuse0;
uniform sampler2D specular0;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 cameraPos;
uniform float ambient;
uniform uint specAmountPow;

vec4 point_light()
{
    vec3 lightVec = lightPos - fragPos;

    float dist = length(lightVec);
    float a = 3.0;
    float b = 0.7;
    float inten = 1.0f / (a * dist * dist + b + dist + 1.0f);

    vec3 _normal = normalize(normal);
    vec3 lightDirec = normalize(lightVec); 

    float diffuse = max(dot(_normal, lightDirec), 0);

    float specularLight = 0.5f;
    vec3 viewDirec = normalize(cameraPos - fragPos);
    vec3 reflectionDirec = reflect(-lightDirec, normal);
    float specAmount = pow(max(dot(viewDirec, reflectionDirec), 0), specAmountPow);
    float specular = specAmount * specularLight;

    return lightColor * (texture(diffuse0, texCoord) * (diffuse * inten + ambient) + specular * inten * texture(specular0, texCoord).r);
}

vec4 direc_light()
{
    vec3 _normal = normalize(normal);
    vec3 lightDirec = normalize(vec3(1.0f, 1.0f, 0.0f));

    float diffuse = max(dot(_normal, lightDirec), 0);

    float specularLight = 0.5f;
    vec3 viewDirec = normalize(cameraPos - fragPos);
    vec3 reflectionDirec = reflect(-lightDirec, normal);
    float specAmount = pow(max(dot(viewDirec, reflectionDirec), 0), specAmountPow);
    float specular = specAmount * specularLight;

    return lightColor * (texture(diffuse0, texCoord) * (diffuse + ambient) + specular * texture(specular0, texCoord).r);
}

vec4 spot_light()
{   
    float outerCone = 0.10f;
    float innerCone = 0.95f;

    vec3 _normal = normalize(normal);
    vec3 lightDirec = normalize(lightPos - fragPos); 

    float diffuse = max(dot(_normal, lightDirec), 0);

    float specularLight = 0.50f;
    vec3 viewDirec = normalize(cameraPos - fragPos);
    vec3 reflectionDirec = reflect(-lightDirec, normal);
    float specAmount = pow(max(dot(viewDirec, reflectionDirec), 0), specAmountPow);
    float specular = specAmount * specularLight;

    float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirec);
    float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

    return lightColor * (texture(diffuse0, texCoord) * (diffuse * inten + ambient) + specular * inten * texture(specular0, texCoord).r);
}

void main()
{

    vec3 _normal = normalize(normal);
    vec3 lightDirec = normalize(lightPos - fragPos); 

    float diffuse = max(dot(_normal, lightDirec), 0);

    float specularLight = 0.5f;
    vec3 viewDirec = normalize(cameraPos - fragPos);
    vec3 reflectionDirec = reflect(-lightDirec, normal);
    float specAmount = pow(max(dot(viewDirec, reflectionDirec), 0), specAmountPow);
    float specular = specAmount * specularLight;

    FragColor = spot_light();
}