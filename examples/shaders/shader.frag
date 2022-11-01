#version 450 core

out vec4 FragColor;

struct Material 
{
    sampler2D diffuse0;
    sampler2D specular0;
    float shininess;
};

struct Light
{   
    // vec3 posistion;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 fragPos;
in vec3 normal;
in vec3 color;
in vec2 texCoords;

uniform Material material;
uniform Light light;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 cameraPos;

vec4 normal_light()
{
    vec3 _normal = normalize(normal);
    vec3 lightDirec = normalize(lightPos - fragPos); 
    
    vec3 ambient = light.ambient * texture(material.diffuse0, texCoords).rgb;

    vec3 diffuse = light.diffuse * max(dot(_normal, lightDirec), 0) * texture(material.diffuse0, texCoords).rgb;

    vec3 viewDir = normalize(cameraPos - fragPos);
    vec3 reflectionDirec = reflect(-lightDirec, normal);
    float specAmount = pow(max(dot(viewDir, reflectionDirec), 0), material.shininess);
    vec3 specular = light.specular * specAmount * texture(material.specular0, texCoords).rgb;

    return vec4(ambient + diffuse + specular, 1.0);
}

vec4 direc_light()
{
    vec3 _normal = normalize(normal);
    vec3 direction = normalize(-light.direction); 

    vec3 ambient = light.ambient * texture(material.diffuse0, texCoords).rgb;

    vec3 diffuse = light.diffuse * max(dot(_normal, direction), 0) * texture(material.diffuse0, texCoords).rgb;

    vec3 viewDir = normalize(cameraPos - fragPos);
    vec3 reflectionDirec = reflect(-direction, normal);
    float specAmount = pow(max(dot(viewDir, reflectionDirec), 0), material.shininess);
    vec3 specular = light.specular * specAmount * texture(material.specular0, texCoords).rgb;
    
    return vec4(ambient + diffuse + specular, 1.0);
}

void main()
{
    FragColor = direc_light();
}


/*
vec4 point_light()
{
    vec3 lightVec = lightPos - fragPos;

    vec3 ambient = lightColor * material.ambient;

    float dist = length(lightVec);
    float a = 3.0;
    float b = 0.7;
    float inten = 1.0f / (a * dist * dist + b + dist + 1.0f);

    vec3 _normal = normalize(normal);
    vec3 lightDirec = normalize(lightVec); 

    vec3 diffuse = lightColor * (max(dot(_normal, lightDirec), 0) * material.diffuse);

    vec3 viewDirec = normalize(cameraPos - fragPos);
    vec3 reflectionDirec = reflect(-lightDirec, normal);
    float specAmount = pow(max(dot(viewDirec, reflectionDirec), 0), material.shininess);
    vec3 specular = lightColor * (specAmount * material.specular);

    return (texture(diffuse0, texCoord) * (diffuse * inten + ambient) + specular * inten * texture(specular0, texCoord).r);
}



vec4 spot_light()
{   
    float outerCone = 0.10f;
    float innerCone = 0.95f;

    vec3 ambient = lightColor * material.ambient;

    vec3 _normal = normalize(normal);
    vec3 lightDirec = normalize(lightPos - fragPos); 

    vec3 diffuse = lightColor *  (max(dot(_normal, lightDirec), 0) * material.diffuse);

    vec3 viewDirec = normalize(cameraPos - fragPos);
    vec3 reflectionDirec = reflect(-lightDirec, normal);
    float specAmount = pow(max(dot(viewDirec, reflectionDirec), 0), material.shininess);
    vec3 specular = lightColor * (specAmount * material.specular);

    float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirec);
    float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

    return (texture(diffuse0, texCoord) * (diffuse * inten + ambient) + specular * inten * texture(specular0, texCoord).r);
}
*/