#version 450 core

layout (location = 0) in vec2 aVertexPosition;
layout (location = 1) in vec2 aTexCoord; // Add this line


out vec3 FragPos;  // Declare the variable to be passed to the fragment shader
out vec2 vTexCoord;

uniform mat3 uModel_to_NDC;

void main()
{
    gl_Position = vec4(vec2(uModel_to_NDC * vec3(aVertexPosition, 1.f)), 0.0, 1.0);
    vTexCoord = aTexCoord; // Pass texture coordinates to the fragment shader
    FragPos = vec3(uModel_to_NDC * vec3(aVertexPosition, 1.f));
}