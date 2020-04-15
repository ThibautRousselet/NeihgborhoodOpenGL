#include "Model.h"

//Constructor with original size
Model::Model(Shader shad, Texture text) {
    shader = shad;
    texture = text;
};

//Constructor with adjustable size ratio
Model::Model(Shader shad, Texture text, glm::vec3 ratio, float nbRep) {
    shader = shad;
    texture = text;
    sizeRatio = ratio;
    nbRepetition = nbRep;
};

Model::Model() {

}

//Function called every frame that render the current model and update the position and animation
void Model::refresh() {
    //next frame of animation
    animate();

    //Put the object at the right position in the world
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    
    model = glm::rotate(model, glm::radians(rotateX), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotateY), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotateZ), glm::vec3(0.0f, 0.0f, 1.0f));

    model = glm::scale(model, sizeRatio);

    shader.useProgram();
    shader.setMat4("model", model);

    glBindVertexArray(vao);
    glActiveTexture(GL_TEXTURE0);
    shader.useProgram();
    glBindTexture(GL_TEXTURE_2D, texture.ID);
    glDrawArrays(GL_TRIANGLES, 0, nbTriangles);
    glBindVertexArray(0);
}

//Animate a model by adding the animvalues to its current values
void Model::animate() {
    //Move the model
    position += animPosition;

    //Reset position when max value is reach
    if (position.x < animMinPosition.x || position.x > animMaxPosition.x) {
        position = animDefaultPosition;
    } else if (position.y < animMinPosition.y || position.y > animMaxPosition.y) {
        position = animDefaultPosition;
    } else if (position.z < animMinPosition.z || position.z > animMaxPosition.z) {
        position = animDefaultPosition;
    }

    //Rotate the model
    rotateX += animRotateX;
    rotateY += animRotateY;
    rotateZ += animRotateZ;

    //Make sure that the values dont increase infinitely
    if (rotateX > 360.0f)
        rotateX -= 360;

    if (rotateY > 360.0f)
        rotateY -= 360;

    if (rotateZ > 360.0f)
        rotateZ -= 360;

    //Same as position for ratio
    sizeRatio += animSizeRatio;
    if (sizeRatio.x < animMinSizeRatio.x || sizeRatio.x > animMaxSizeRatio.x) {
        sizeRatio = animDefaultSizeRatio;
    }
    else if (sizeRatio.y < animMinSizeRatio.y || sizeRatio.y > animMaxSizeRatio.y) {
        sizeRatio = animDefaultSizeRatio;
    }
    else if (sizeRatio.z < animMinSizeRatio.z || sizeRatio.z > animMaxSizeRatio.z) {
        sizeRatio = animDefaultSizeRatio;
    }
}