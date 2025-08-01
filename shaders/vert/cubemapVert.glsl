#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 vpm;

void main()
{
    TexCoords = aPos;
    gl_Position = vpm * vec4(aPos, 1.0);
}  