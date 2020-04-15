#version 430 core

in vec3 position;

out vec3 vTexturePos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 worldPosition;

void main()
{
    vTexturePos = position;
    gl_Position = projection * view * vec4(position, 1);
}
