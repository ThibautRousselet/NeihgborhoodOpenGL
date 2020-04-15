#version 430 core

in vec4 position;
in vec4 colors;
in vec2 texturePos;

out vec2 vTexturePos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 worldPosition;

void main()
{
    gl_Position = worldPosition + projection * view * model * (position);
    vTexturePos = vec2(texturePos.x, texturePos.y);
}
