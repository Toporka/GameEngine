#version 330 core
layout (location = 0) in vec2 vertex;
layout (location = 1) in vec2 texturePosition;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    TexCoords = texturePosition;
    gl_Position = projection * model * vec4(vertex, 0.0, 1.0);
}