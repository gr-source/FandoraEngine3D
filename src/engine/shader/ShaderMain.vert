#version 330 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTextCoord;
layout(location = 3) in mat4 inModelMatrix;

uniform mat4 projection;
uniform mat4 view;

uniform vec3 viewPos;
uniform float scale;

out vec3 m_normal;
out vec3 m_fragPos;
out vec3 m_viewPos;
out vec2 m_TexCoord;

void main() {
    m_fragPos = vec3(inModelMatrix * vec4(inPosition, 1.0));

    m_normal = mat3(transpose(inverse(inModelMatrix))) * inNormal;

    m_viewPos = viewPos;
    m_TexCoord =  inTextCoord * scale;

    gl_Position = projection * view * vec4(m_fragPos, 1.0);
}