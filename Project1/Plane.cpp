#include "Plane.h"
//Build a plane with the given attributes
Plane::Plane(Shader shad, Texture text) : Model(shad, text) {
    InitBuffer();
    nbTriangles = 6;
};

Plane::Plane(Shader shad, Texture text, glm::vec3 ratio, float nbRep) : Model(shad, text, ratio, nbRep) {
    InitBuffer();
    nbTriangles = 6;
};

Plane::Plane() {

};

void Plane::InitBuffer() {

    float vertices[] = {
        // positions           // texture
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f,
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,

         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
    };
    //We multiply the texturepos to display the texture multiples times on the ground I could add a number of repition variable but I needed it just once
    for (int i = 0; i < 30; i+=5) {
        vertices[i + 3] *= nbRepetition;
        vertices[i + 4] *= nbRepetition;
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
    GLuint texture_id = glGetAttribLocation(shader.ID, "texturePos");

    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(position_id, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(position_id);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(texture_id, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(texture_id);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
};