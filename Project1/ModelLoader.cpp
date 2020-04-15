#include "ModelLoader.h"

//Load model from file using the obsloader
ModelLoader::ModelLoader(const char* pat, Shader shad, Texture text) : Model(shad, text) {
    path = pat;
    InitBuffer();
    nbTriangles = vertices.size() * 3;
};
ModelLoader::ModelLoader() {

};

void ModelLoader::InitBuffer() {
    
    bool res = loadOBJ(path, vertices, uvs, normals);

    int size = vertices.size();

    //I go through a dynamicaly alocated array to keep the same buffer initialization functions as the other ones with static arrays
    //It is not optimized as the values are all copied
    float* tmpArray = new float[size*5];
    for (int i = 0; i < size; i++) {
        tmpArray[i * 5] = vertices[i].x;
        tmpArray[i * 5 + 1] = vertices[i].y;
        tmpArray[i * 5 + 2] = vertices[i].z;
        tmpArray[i * 5 + 3] = uvs[i].x;
        tmpArray[i * 5 + 4] = uvs[i].y;
    }


    GLuint vbo;
    // Generate buffer object names (in this case 1)
    glGenBuffers(1, &vbo);

    // Bind named buffer object
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Create and initialize buffer object’s data store
    glBufferData(GL_ARRAY_BUFFER, size * 5*sizeof(float), tmpArray, GL_STATIC_DRAW);

    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

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

    delete[] tmpArray;
}