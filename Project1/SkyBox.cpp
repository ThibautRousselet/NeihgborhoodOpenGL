#include "SkyBox.h"
//Constructor of the skybox
SkyBox::SkyBox(Shader shad, Texture text) : Model(shad, text) {
    InitBuffer();
    nbTriangles = 36;
};

SkyBox::SkyBox() {

};

//Render the skybox, disable the septhMask while doing so
void SkyBox::refresh() {

    glDepthMask(GL_FALSE);
    shader.useProgram();
    glBindVertexArray(vao);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture.ID);
    glDrawArrays(GL_TRIANGLES, 0, nbTriangles);
    glDepthMask(GL_TRUE);
}

void SkyBox::InitBuffer() {
    GLfloat vertices[] = {
        // positions          
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
    };
    for (int i = 0; i < 108; i++) {
        vertices[i] *= 150;
    }
    GLuint vbo;
    // Generate buffer object names (in this case 1)
    glGenBuffers(1, &vbo);

    // Bind named buffer object
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Create and initialize buffer object’s data store
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Location of attribute variable
    GLuint position_id = glGetAttribLocation(shader.ID, "position");

    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(position_id, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(position_id);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
};