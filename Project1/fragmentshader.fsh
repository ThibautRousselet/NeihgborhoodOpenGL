#version 430 core

in vec2 vTexturePos;

uniform sampler2D sTexture;

void main()
{
    float ambientStrength = 0.8;
    gl_FragColor = texture(sTexture, vTexturePos) * ambientStrength;
}
