#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;
out vec2 View;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    // Position in world space
    FragPos = vec3(model * vec4(aPos, 1.0));

    // Normal vector transformation (convert normal to world space)
    Normal = mat3(transpose(inverse(model))) * aNormal;

    // Pass texture coordinates to the fragment shader
    TexCoords = aTexCoords;

    // Final vertex position
    gl_Position = projection * view * vec4(FragPos, 1.0);
}
