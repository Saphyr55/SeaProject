#version 450 core

out vec4 FragColor;

in vec3 fragPos;
in vec3 normal;
in vec3 color;
in vec2 texCoords;

struct Material 
{
    sampler2D diffuse0;
    sampler2D specular0;
    float shininess;
};

struct Light
{   
    vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

    float cutOff;
    float outerCutOff;
};

uniform Material material;
uniform Light light;

uniform vec4 lightColor;
uniform vec3 cameraPos;

vec3 get_ambient()
{
    return light.ambient * texture(material.diffuse0, texCoords).rgb;
}

vec3 get_diffuse(vec3 _normal, vec3 lightDirec)
{
    return light.diffuse * max(dot(_normal, lightDirec), 0) * texture(material.diffuse0, texCoords).rgb;
}

vec3 get_specular(vec3 _normal, vec3 lightDirec)
{
    vec3 viewDir = normalize(cameraPos - fragPos);
    vec3 reflectionDirec = reflect(-lightDirec, normal);
    float specAmount = pow(max(dot(viewDir, reflectionDirec), 0), material.shininess);
    return light.specular * specAmount * texture(material.specular0, texCoords).rgb;
}

vec4 point_light()
{
    vec3 _normal = normalize(normal);
    vec3 lightDirec = normalize(light.position - fragPos); 
    
    vec3 ambient = get_ambient();
    vec3 diffuse = get_diffuse(_normal, lightDirec);
    vec3 specular = get_specular(_normal, lightDirec);

    float _distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * _distance + light.quadratic * (_distance * _distance));  

    ambient  *= attenuation; 
    diffuse  *= attenuation;
    specular *= attenuation; 

    return vec4(ambient + diffuse + specular, 1.0);
}

vec4 direc_light()
{
    vec3 _normal = normalize(normal);
    vec3 direction = normalize(-light.direction); 

    return vec4(get_ambient() + get_diffuse(_normal, direction) + get_specular(_normal, direction), 1.0);
}

vec4 spot_light()
{   
    vec3 _normal = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos); 

    vec3 ambient = get_ambient();
    vec3 diffuse = get_diffuse(_normal, lightDir);
    vec3 specular = get_specular(_normal, lightDir);

    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon   = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0); 
    diffuse  *= intensity;
    specular *= intensity;

    float _distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * _distance + light.quadratic * (_distance * _distance));  
    ambient  *= attenuation; 
    diffuse  *= attenuation;
    specular *= attenuation; 

    return vec4(ambient + diffuse + specular, 1.0) ;
}

void main()
{
    FragColor = point_light();
}
