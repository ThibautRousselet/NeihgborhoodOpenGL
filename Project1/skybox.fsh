#version 430 core

in vec3 vTexturePos;

uniform samplerCube sTexture;

void main()
{
    gl_FragColor = texture(sTexture, vTexturePos);
}
