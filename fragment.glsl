#version 330 core

in vec3 ourColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform sampler2D texture1;
uniform int useTexture;

// Właściwości światła
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;

// Włączanie/wyłączanie składowych
uniform bool useAmbient;
uniform bool useDiffuse;
uniform bool useSpecular;

// Parametry światła
uniform float ambientStrength;
uniform float specularStrength;
uniform int shininess;

void main() {
    vec4 objectColor;
    
    if (useTexture == 1) {
        objectColor = texture(texture1, TexCoord);
    } else {
        objectColor = vec4(ourColor, 1.0);
    }
    
    // Ambient (światło otoczenia)
    vec3 ambient = vec3(0.0);
    if (useAmbient) {
        ambient = ambientStrength * lightColor;
    }
    
    // Diffuse (światło rozproszone)
    vec3 diffuse = vec3(0.0);
    if (useDiffuse) {
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        diffuse = diff * lightColor;
    }
    
    // Specular (światło odbłysków)
    vec3 specular = vec3(0.0);
    if (useSpecular) {
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
        specular = specularStrength * spec * lightColor;
    }
    
    vec3 result = (ambient + diffuse + specular);
    FragColor = vec4(result, 1.0) * objectColor;
}