#pragma once
#include "Shader.h"
#include "Texture.h"

class Model
{
public:
    Model(Shader shad, Texture text);
    Model(Shader shad, Texture text, glm::vec3 sizeR, float nbRep);
    Model();
    virtual void refresh();
    virtual void animate();
    virtual void InitBuffer() = 0;   // Initialize vbo, vao

    GLuint vao;
    Shader shader;
    Texture texture;

    //Position values
    glm::vec3 position;
    float rotateX = 0.0f;
    float rotateY = 0.0f;
    float rotateZ = 0.0f;

    glm::vec3 sizeRatio = glm::vec3(1.0f, 1.0f, 1.0f);
    float nbRepetition = 1.0f; //Number of repetition of the texture

    int nbTriangles = 0;

    //ANIMATION
    //animation value, value added each frame to the position values to animate a model
    glm::vec3 animPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    float animRotateX = 0.0f;
    float animRotateY = 0.0f;
    float animRotateZ = 0.0f;

    glm::vec3 animSizeRatio = glm::vec3(0.0f, 0.0f, 0.0f);

    //Max animation values define the limit of the animation, when reached, value is set back to default (ex car comes back to startng point)
    glm::vec3 animMaxPosition = glm::vec3(100000.0f, 100000.0f, 100000.0f);
    glm::vec3 animMinPosition = glm::vec3(-100000.0f, -100000.0f, -100000.0f);
    glm::vec3 animDefaultPosition = glm::vec3(0.0f, 0.0f, 0.0f);

    //Same for the size ratio
    glm::vec3 animMinSizeRatio = glm::vec3(-100000.0f, -100000.0f, -100000.0f);
    glm::vec3 animMaxSizeRatio = glm::vec3(100000.0f, 100000.0f, 100000.0f);
    glm::vec3 animDefaultSizeRatio = glm::vec3(1.0f, 1.0f, 1.0f);

    
};

