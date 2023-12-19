#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;

    vec3 color;
    sampler2D texture;
    bool hasTexture;
};

struct DirLight {
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 FragColor;

in vec3 m_fragPos;
in vec3 m_normal;
in vec3 m_viewPos;
in vec2 m_TexCoord;

uniform Material material;
uniform DirLight dirLight;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);

void main() {
    // define an output color value
    vec3 outputColor = vec3(0.0, 0.0, 0.0);

    // calc view direction
    //vec3 viewDir = normalize(m_viewPos - m_fragPos);
    vec3 viewDir = normalize(-m_fragPos);


    // add the directional light's contribution to the output
    outputColor += CalcDirLight(dirLight, m_normal, viewDir);

    if (material.hasTexture) {
        FragColor = texture(material.texture, m_TexCoord) * vec4(outputColor, 1.0);
    } else {
        FragColor = vec4(outputColor, 1.0);
    }
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient  = light.ambient  * material.ambient;
    vec3 diffuse  = light.diffuse  * diff * material.diffuse;
    vec3 specular = light.specular * spec * material.specular;
    return (ambient + diffuse + specular);
}
