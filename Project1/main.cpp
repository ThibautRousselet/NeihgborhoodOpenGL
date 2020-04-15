#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glsl.h"

using namespace std;

#include <glm/gtc/matrix_transform.hpp>


#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "Cube.h"
#include "SkyBox.h"
#include "Plane.h"
#include "ModelLoader.h"
#include "Builder.h"



//--------------------------------------------------------------------------------
// Consts
//--------------------------------------------------------------------------------

const int WIDTH = 1200, HEIGHT = 800;
const std::string resDir = std::string("Resources/");
//--------------------------------------------------------------------------------
// Variables
//--------------------------------------------------------------------------------

// ID's
Shader shader;
Shader skyBoxShader;
Camera camera;

SkyBox skyBox;
vector<Cube> cubes = vector<Cube>();
vector<Plane> planes = vector<Plane>();
vector<ModelLoader> models = vector<ModelLoader>();

GLuint vao;

//Camera
glm::mat4 viewMatrix = glm::mat4(1.0f);
glm::mat4 modelMatrix = glm::mat4(1.0f);
glm::mat4 projectionMatrix;



//--------------------------------------------------------------------------------
// Keyboard handling
//--------------------------------------------------------------------------------

void keyboardHandler(unsigned char key, int a, int b)
{
    if (key == 27)
        glutExit();

    //Camera movement input 
    camera.handleCameraInput(key);
}


//--------------------------------------------------------------------------------
// Rendering
//--------------------------------------------------------------------------------

void Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera.updateView();
    skyBoxShader.useProgram();
    skyBoxShader.setMat4("view", camera.view);
    skyBox.refresh();

    //All the models are stored in vectors and their refresh function is called every frame
   shader.useProgram();
   shader.setMat4("view", camera.view);
   for (int i = 0; i < cubes.size(); i++) {
       cubes[i].refresh();
   }
   shader.useProgram();
   shader.setMat4("view", camera.view);
   for (int i = 0; i < planes.size(); i++) {
       planes[i].refresh();
   }
   shader.useProgram();
   for (int i = 0; i < models.size(); i++) {
       models[i].refresh();
   }

   glutSwapBuffers();
   glutPostRedisplay();
}

//Set up the skybox and loads its textures
void initSkyBox() {
    vector<std::string> faces
    {
        resDir + "Textures/negx.jpg",
        resDir + "Textures/posx.jpg",
        resDir + "Textures/posy.jpg",
        resDir + "Textures/negy.jpg",
        resDir + "Textures/negz.jpg",
        resDir + "Textures/posz.jpg"
    };
    Texture skyBoxTexture = Texture(faces);
    skyBox = SkyBox(skyBoxShader, skyBoxTexture);
}
//------------------------------------------------------------
// void InitGlutGlew(int argc, char **argv)
// Initializes Glut and Glew
//------------------------------------------------------------

void InitGlutGlew(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Final Assignment Thibaut Rousselet");
    glutDisplayFunc(Render);
    glutKeyboardFunc(keyboardHandler);

    glewInit();
}

//set up the camera and initialize uniform values
void InitCamera() {
    glEnable(GL_DEPTH_TEST);

    modelMatrix = glm::rotate(modelMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));
    projectionMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 500.0f);

    shader.useProgram();
    shader.setMat4("model", modelMatrix);

    shader.useProgram();
    shader.setMat4("view", viewMatrix);

    shader.useProgram();
    shader.setMat4("projection", projectionMatrix);

    skyBoxShader.useProgram();
    skyBoxShader.setMat4("model", modelMatrix);

    skyBoxShader.useProgram();
    skyBoxShader.setMat4("view", viewMatrix);

    skyBoxShader.useProgram();
    skyBoxShader.setMat4("projection", projectionMatrix);

}
//------------------------------------------------------------
// void InitShaders()
// Initializes the fragmentshader and vertexshader
//------------------------------------------------------------

void InitShaders()
{
    shader = Shader("vertexshader.vsh", "fragmentshader.fsh");
    skyBoxShader = Shader("skybox.vsh", "skybox.fsh");
}

//The models are loaded and created in the builder object to lighten the main
void InitModels() 
{
    Builder builder = Builder();
    builder.buildFloor(planes, shader);
    builder.buildTrees(models, shader);
    builder.buildBuilding(cubes, models, shader);
    builder.buildCar(models, shader);
}


int main(int argc, char** argv)
{
    
    InitGlutGlew(argc, argv);
    InitShaders();
    InitModels();
    initSkyBox();
    InitCamera();

    // Hide console window
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);

    // Main loop
    glutMainLoop();

    return 0;
}
