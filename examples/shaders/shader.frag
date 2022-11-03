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
    sampler2D ambient0;
    float shininess0;
};

struct DirectionalLight
{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 position;
    float constant;
    float linear;
    float quadratic;
};

struct SpotLight
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
uniform float ambientWorld;

#define MAX_SPOT_LIGHTS 32
#define MAX_POINT_LIGHTS 32
#define MAX_DIREC_LIGHTS 2

uniform int sizeSpotLight;
uniform int sizePointLight;
uniform int sizeDirectionalLight;

uniform SpotLight spotLights[MAX_SPOT_LIGHTS];
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform DirectionalLight directionalLights[MAX_DIREC_LIGHTS];

uniform vec4 lightColor;
uniform vec3 cameraPos;

uniform bool useFlog;

vec3 get_ambient(vec3 light_ambient)
{
    return light_ambient * texture(material.ambient0, texCoords).rgb;
}

vec3 get_diffuse(vec3 light_diffuse, vec3 _normal, vec3 light_direc)
{
    return light_diffuse * max(dot(_normal, light_direc), 0) * texture(material.diffuse0, texCoords).rgb;
}

vec3 get_specular(vec3 light_specular, vec3 _normal, vec3 light_direc, vec3 view_dir)
{
    vec3 reflectionDirec = reflect(-light_direc, normal);
    float specAmount = pow(max(dot(view_dir, reflectionDirec), 0), material.shininess0);
    return light_specular * specAmount * texture(material.specular0, texCoords).rgb;
}

vec3 create_point_light(PointLight light, vec3 _normal, vec3 fragPos, vec3 view_dir)
{
    vec3 light_direc = normalize(light.position - fragPos); 
    
    vec3 ambient = get_ambient(light.ambient);
    vec3 diffuse = get_diffuse(light.diffuse, _normal, light_direc);
    vec3 specular = get_specular(light.specular, _normal, light_direc, view_dir);

    float _distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * _distance + light.quadratic * (_distance * _distance));  

    ambient  *= attenuation; 
    diffuse  *= attenuation;
    specular *= attenuation; 

    return (ambient + diffuse + specular);
}

vec3 create_direc_light(DirectionalLight light, vec3 _normal, vec3 fragPos, vec3 view_dir)
{   
    vec3 direction = normalize(-light.direction); 
    return (
        get_ambient(light.ambient) + 
        get_diffuse(light.diffuse, _normal, direction) + 
        get_specular(light.specular, _normal, direction, view_dir)
    );
}

vec3 create_spot_light(SpotLight light, vec3 _normal, vec3 fragPos, vec3 view_dir)
{   
    vec3 lightDir = normalize(light.position - fragPos); 

    vec3 ambient = get_ambient(light.ambient);
    vec3 diffuse = get_diffuse(light.diffuse,_normal, lightDir);
    vec3 specular = get_specular(light.specular, _normal, lightDir, view_dir);

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

    return (ambient + diffuse + specular) ;
}

float linearize_depth(float _depth, float far, float near)
{
    return (2.0 * near * far) / (far + near - (_depth * 2.0 - 1.0) * (far - near));
}

float logistic_depth(float _depth, float far, float near, float steepness = 0.5, float offset = 5.0)
{
    float zVal = linearize_depth(_depth, far, near);
    return (1 / (1 + exp(-steepness * (zVal - offset))));
}

void main()
{   
    vec4 _result = vec4(0.0);
    vec3 view_dir = normalize(fragPos);
    vec3 _normal =  normalize(normal);

    vec3 _output_light = vec3(0.0);

    for (int i = 0 ; i < sizePointLight ; i++)
        _output_light += create_point_light(pointLights[i], _normal, fragPos, view_dir);

    for (int i = 0 ; i < sizeDirectionalLight ; i++)
        _output_light += create_direc_light(directionalLights[i], _normal, fragPos, view_dir);

    for (int i = 0 ; i < sizeSpotLight ; i++)
        _output_light += create_spot_light(spotLights[i], _normal, fragPos, view_dir);
    
    _result += vec4(_output_light, 1.0);

    // float depth = logistic_depth(gl_FragCoord.z, near, far); 
    
    // vec4 v_depth = (1.0f - depth) + vec4(depth * vec3(0.11f, 0.11f, 0.11f), 1.0);
    // if(useFlog) _result *= v_depth;

    FragColor = _result; 
}
