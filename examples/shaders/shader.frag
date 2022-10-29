#version 330 core

out vec4 FragColor;

in vec2 texCoord;
in vec3 color;
in vec3 normal;
in vec3 crntPos;

uniform sampler2D tex0;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 cameraPos;

void main()
{
    float ambiant = 0.20f;

    vec3 _normal = normalize(normal);
    vec3 lightDirec = normalize(lightPos - crntPos); 

    float diffuse = max(dot(_normal, lightDirec), 0);

    float specularLight = 0.5f;
    vec3 viewDirec = normalize(cameraPos - crntPos);
    vec3 reflectionDirec = reflect(-lightDirec, normal);
    float specAmount = pow(max(dot(viewDirec, reflectionDirec), 0), 8);
    float specular = specAmount * specularLight;

    FragColor = texture(tex0, texCoord) * lightColor * (diffuse + ambiant + specular);
}