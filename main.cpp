//
//  main.cpp
//  3D Object Drawing
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "basic_camera.h"
#include "pointLight.h"
#include "sphere.h"
#include "spotLight.h"
#include "directionLight.h"
#include "cube.h"
#include "stb_image.h"
#include "curve.h"
#include "sphere.h"
#include "octagon.h"
#include "pyramid.h"
#include "halfsphere.h"
#include <iostream>
#include <chrono>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model, float r, float g, float b);
//void bed(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void drawField(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void drawFieldWithTexture(Shader& lightingShader, glm::mat4 alTogether);
void drawBase(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void drawFrontLake(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void drawLake(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void drawMain(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void drawEntrance(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void drawSideFrame(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void drawRoof(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void drawTreeWithFractiles(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float L, float H, float W, int N);
void drawTajmahal(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void drawSemiDome(unsigned int& cubeVAO, BezierCurve& semiDome, Octagon& base, Octagon& mid, Shader& lightingShader, glm::mat4 alTogether);
void drawDome(unsigned int& cubeVAO, BezierCurve& semiDome, Octagon& base, Shader& lightingShader, glm::mat4 alTogether);
void drawFloor(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void drawCylindricalTree(BezierCurve& CylinderGreen, BezierCurve& CylinderGrey, Shader& lightingShader, glm::mat4 alTogether);
void drawNormalTree(BezierCurve& NormalTree, BezierCurve& CylinderGrey, Shader& lightingShader, glm::mat4 alTogether);
void drawTrees(BezierCurve& NormalTree, BezierCurve& CylinderGreen, BezierCurve& CylinderGrey, Shader& lightingShader, glm::mat4 alTogether);
void drawMinar(unsigned int& cubeVAO, BezierCurve& cylinder, BezierCurve& semiDome, Octagon& base, Octagon& oct, Shader& lightingShader, glm::mat4 alTogether);
void drawNarrowMinar(unsigned int& cubeVAO, BezierCurve& cylinder, BezierCurve& semiDome, Octagon& base, Octagon& oct, Shader& lightingShader, glm::mat4 alTogether);
void drawNarrowMinar1(unsigned int& cubeVAO, BezierCurve& cylinder, BezierCurve& semiDome, Octagon& base, Octagon& oct, Shader& lightingShader, glm::mat4 alTogether);
void drawNarrowMinarTogether(unsigned int& cubeVAO, BezierCurve& minar, BezierCurve& semiDome, Octagon& oct3, Octagon& oct2, Shader& lightingShader, glm::mat4 next); 
void updateClockHandAngles(float& hourAngle, float& minuteAngle);
void drawClockHands(unsigned int cubeVAO, Shader& ourShader);
void drawClockHandsAndDials(unsigned int cubeVAO, Shader& ourShader);
unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax);
void updatePositions(float deltaTime);





// settings
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 1000;



// camera
Camera camera(glm::vec3(0.0f, 35.0f, 135.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float eyeX = 0.0, eyeY = 1.0, eyeZ = 3.0;
float lookAtX = 0.0, lookAtY = 0.0, lookAtZ = 0.0;
glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);
//BasicCamera basic_camera(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, V);

//bird's eye view
bool birdEyeView = false;
glm::vec3 birdEyePosition(2.0f, 50.0f, 80.5f);
glm::vec3 birdEyeTarget(2.0f, 0.0f, 7.5f);
float birdEyeSpeed = 5.0f;

// positions of the point lights
// Existing positions of the point lights
glm::vec3 pointLightPositions[] = {
    glm::vec3(2.50f,  20.50f,  -28.0f),
    glm::vec3(2.50f,  20.5f,  -18.0f),
    glm::vec3(-2.5f,  20.5f,  -28.0f),
    glm::vec3(-2.5f,  20.5f,  -18.0f),
    glm::vec3(11.0f, 15.3f, 36.2f),
    glm::vec3(17.0f, 15.3f, 60.0f),
    glm::vec3(11.0f, 15.3f, 60.0f),
    glm::vec3(17.0f, 15.3f, 35.2f)
};


glm::vec3 spotLightPosition = glm::vec3(0.0f, 20.5f, 68.0f);

SpotLight spotlight(

    spotLightPosition.x, spotLightPosition.y, spotLightPosition.z,  // position
    0.0f, -1.0f, 0.0f,   //direction
    0.0f, 0.5f, 0.5f,    // ambient
    0.0f, 1.0f, 1.0f,    // diffuse
    0.0f, 1.0f, 1.0f,    // specular
    0.05f,   //k_c
    0.009f,  //k_l
    0.0032f, //k_q
    60,     //light angle
    5       // light number
);

DirectionLight moonlight(

    0.0f, -1.0f, -0.5f,   //direction
    0.031f, 0.04f, 0.045f,    // ambient
    0.031f, 0.04f, 0.45f,    // diffuse
    1.0f, 1.0f, 1.0f,    // specular
    7       // light number
);

DirectionLight daylight(

    0.0f, -1.0f, -0.5f,   //direction
    0.4f, 0.4f, 0.4f,    // ambient
    0.8f, 0.8f, 0.8f,    // diffuse
    1.0f, 1.0f, 1.0f,    // specular
    6       // light number
);

// Existing point lights
PointLight pointlight1(
    pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z,  // position
    0.1f, 0.05f, 0.1f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    1       // light number
);

PointLight pointlight2(
    pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z,  // position
    0.05f, 0.05f, 0.15f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    2       // light number
);

PointLight pointlight3(
    pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z,  // position
    0.05f, 0.1f, 0.1f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    3       // light number
);

PointLight pointlight4(
    pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z,  // position
    0.1f, 0.1f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    4       // light number
);

// New point lights for minarets
PointLight pointlight5(
    pointLightPositions[4].x, pointLightPositions[4].y, pointLightPositions[4].z,  // position
    0.1f, 0.1f, 0.1f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    0.032f,   //k_c
    0.032f,  //k_l
    0.032f, //k_q
    5       // light number
);

PointLight pointlight6(
    pointLightPositions[5].x, pointLightPositions[5].y, pointLightPositions[5].z,  // position
    0.1f, 0.1f, 0.1f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    0.032f,   //k_c
    0.032f,  //k_l
    0.032f, //k_q
    6       // light number
);

PointLight pointlight7(
    pointLightPositions[6].x, pointLightPositions[6].y, pointLightPositions[6].z,  // position
    0.1f, 0.1f, 0.1f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    0.032f,   //k_c
    0.032f,  //k_l
    0.032f, //k_q
    7       // light number
);

PointLight pointlight8(
    pointLightPositions[7].x, pointLightPositions[7].y, pointLightPositions[7].z,  // position
    0.1f, 0.1f, 0.1f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    0.032f,   //k_c
    0.032f,  //k_l
    0.032f, //k_q
    8       // light number
);



// light settings
bool pointLightOn = true;
bool spotLightOn = true;
bool dayLightOn = true;
bool moonLightOn = true;
bool ambientToggle = true;
bool diffuseToggle = true;
bool specularToggle = true;


// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;


// Global variables for positions
float carZPosition = 0.0f;  // Position of the car along z-axis
float boatXPosition = 0.0f; // Position of the boat along x-axis

// Movement states
bool isCarMoving = false;
bool isBoatMoving = false;

// Speeds
const float carSpeed = 5.0f;
const float boatSpeed = 3.0f;



int main()
{

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CSE 4208: Computer Graphics Laboratory", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    //glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader lightingShader("vertexShaderForPhongShading.vs", "fragmentShaderForPhongShading.fs");
    //Shader lightingShader("vertexShaderForGouraudShading.vs", "fragmentShaderForGouraudShading.fs");
    //Shader lightingShaderWithTexture("vertexShaderForPhongShadingWithTexture.vs", "fragmentShaderForPhongShadingWithTexture.fs");
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");
    Shader waterShader("waterVertexShader.vs", "waterFragmentShader.fs");
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float treeVertices[] = {                            //46 vertices
            0.0, 0.5700, 5.1000,
        -0.1850, 0.4800, 5.1000,
        -0.4550, 0.3800, 5.1000,
        -0.6950, 0.2950, 5.1000,
        -0.8800, 0.2500, 5.1000,
        -1.0150, 0.2500, 5.1000,
        -1.1600, 0.2700, 5.1000,
        -1.3200, 0.3600, 5.1000,
        -1.4350, 0.5300, 5.1000,
        -1.4800, 0.7550, 5.1000,
        -1.4650, 0.8850, 5.1000,
        -1.4050, 0.9650, 5.1000,
        -1.3200, 1.0400, 5.1000,
        -1.2250, 1.0700, 5.1000,
        -1.0950, 1.1250, 5.1000,
        -1.0000, 1.1550, 5.1000,
        -0.8650, 1.1850, 5.1000,
        -0.8550, 1.2150, 5.1000,
        -0.9400, 1.2500, 5.1000,
        -1.1000, 1.2500, 5.1000,
        -1.1750, 1.2500, 5.1000,
        -1.2700, 1.2550, 5.1000,
        -1.3800, 1.3300, 5.1000,
        -1.4750, 1.4300, 5.1000,
        -1.4850, 1.5650, 5.1000,
        -1.4950, 1.6600, 5.1000,
        -1.4850, 1.7950, 5.1000,
        -1.4550, 1.8700, 5.1000,
        -1.4150, 1.9450, 5.1000,
        -1.3200, 1.9750, 5.1000,
        -1.1400, 2.0000, 5.1000,
        -1.0250, 1.9700, 5.1000,
        -0.8400, 1.9100, 5.1000,
        -0.7600, 1.8700, 5.1000,
        -0.7150, 1.8600, 5.1000,
        -0.7750, 1.9600, 5.1000,
        -0.8050, 2.0450, 5.1000,
        -0.7950, 2.1650, 5.1000,
        -0.7300, 2.3000, 5.1000,
        -0.5950, 2.3800, 5.1000,
        -0.4650, 2.4300, 5.1000,
        -0.3750, 2.4500, 5.1000,
        -0.2250, 2.4750, 5.1000,
        -0.1450, 2.4800, 5.1000,
        -0.0550, 2.5000, 5.1000,
        0.0, 2.5000, 5.1000,
    };

    float minarVertices[] = {
         -0.77, 0.0, 5.1000,
         -0.76, 0.1, 5.1000,
         -0.75, 0.2, 5.1000,
         -0.74, 0.3, 5.1000,
         -0.73, 0.4, 5.1000,
         -0.72, 0.5, 5.1000,
         -0.71, 0.6, 5.1000,
         -0.70, 0.7, 5.1000,
         -0.69, 0.8, 5.1000,
         -0.68, 0.9, 5.1000,
         -0.67, 1.0, 5.1000,
         -0.66, 1.1, 5.1000,
         -0.65, 1.2, 5.1000,
         -0.64, 1.3, 5.1000,
         -0.63, 1.4, 5.1000,
         -0.62, 1.5, 5.1000,
         -0.61, 1.6, 5.1000,
         -0.60, 1.7, 5.1000,
         -0.59, 1.8, 5.1000,
         -0.58, 1.9, 5.1000,
    };

    float solinoidVertices[] = {
          0.0 , 0.0, 5.1000,
         -0.77, 0.0, 5.1000,
         -0.76, 0.1, 5.1000,
         -0.75, 0.2, 5.1000,
         -0.74, 0.3, 5.1000,
         -0.73, 0.4, 5.1000,
         -0.72, 0.5, 5.1000,
         -0.71, 0.6, 5.1000,
         -0.70, 0.7, 5.1000,
         -0.69, 0.8, 5.1000,
         -0.68, 0.9, 5.1000,
         -0.67, 1.0, 5.1000,
         -0.66, 1.1, 5.1000,
         -0.65, 1.2, 5.1000,
         -0.64, 1.3, 5.1000,
         -0.63, 1.4, 5.1000,
         -0.62, 1.5, 5.1000,
         -0.61, 1.6, 5.1000,
         -0.60, 1.7, 5.1000,
         -0.59, 1.8, 5.1000,
         -0.58, 1.9, 5.1000,
          0.0 , 1.9, 5.1000
    };

    float domeVerties[] = {
        -0.7700, 0.4150, 5.1000,
        -0.7650, 0.5250, 5.1000,
        -0.7700, 0.6200, 5.1000,
        -0.7650, 0.7300, 5.1000,
        -0.8450, 0.8150, 5.1000,
        -0.9100, 0.8900, 5.1000,
        -0.9700, 0.9850, 5.1000,
        -1.0000, 1.0550, 5.1000,
        -1.0200, 1.1550, 5.1000,
        -1.0300, 1.2600, 5.1000,
        -1.0150, 1.3400, 5.1000,
        -1.0000, 1.4300, 5.1000,
        -0.9500, 1.5000, 5.1000,
        -0.8950, 1.5800, 5.1000,
        -0.8150, 1.6250, 5.1000,
        -0.7550, 1.6800, 5.1000,
        -0.6850, 1.7500, 5.1000,
        -0.5900, 1.8100, 5.1000,
        -0.5150, 1.8650, 5.1000,
        -0.4100, 1.9250, 5.1000,
        -0.2800, 2.0300, 5.1000,
        -0.1800, 2.1050, 5.1000,
        -0.0900, 2.1950, 5.1000,
        -0.0300, 2.3050, 5.1000,
        0.0, 2.4600, 5.1000
    };

    float semiDomeVerties[] = {
        -1.0000, 1.0550, 5.1000,
        -1.0200, 1.1550, 5.1000,
        -1.0300, 1.2600, 5.1000,
        -1.0150, 1.3400, 5.1000,
        -1.0000, 1.4300, 5.1000,
        -0.9500, 1.5000, 5.1000,
        -0.8950, 1.5800, 5.1000,
        -0.8150, 1.6250, 5.1000,
        -0.7550, 1.6800, 5.1000,
        -0.6850, 1.7500, 5.1000,
        -0.5900, 1.8100, 5.1000,
        -0.5150, 1.8650, 5.1000,
        -0.4100, 1.9250, 5.1000,
        -0.2800, 2.0300, 5.1000,
        -0.1800, 2.1050, 5.1000,
        -0.0900, 2.1950, 5.1000,
        -0.0300, 2.3050, 5.1000,
         0.0,    2.4600, 5.1000
    };

    float waterVertices[] = {
        // Positions          // Texture Coords
        5.0f, 0.01f,  5.0f,   1.0f, 0.0f,
       -5.0f, 0.01f,  5.0f,   0.0f, 0.0f,
       -5.0f, 0.01f, -5.0f,   0.0f, 1.0f,
        5.0f, 0.01f, -5.0f,   1.0f, 1.0f
    };


    unsigned int waterIndices[] = { 0, 1, 2, 0, 2, 3 };

    unsigned int waterVAO, waterVBO, waterEBO;
    glGenVertexArrays(1, &waterVAO);
    glGenBuffers(1, &waterVBO);
    glGenBuffers(1, &waterEBO);

    glBindVertexArray(waterVAO);
    glBindBuffer(GL_ARRAY_BUFFER, waterVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(waterVertices), waterVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, waterEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(waterIndices), waterIndices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    glm::vec4 domeAmbient = glm::vec4(1.0, 1.0, 0.8, 1.0);
    glm::vec4 domeDiffusive = glm::vec4(1.0, 1.0, 0.8, 1.0);
    glm::vec4 domeSpecular = glm::vec4(1.0, 1.0, 0.8, 1.0);
    float domeShiny = 32.0f;

    BezierCurve dome = BezierCurve(domeVerties, 75, domeAmbient, domeDiffusive, domeSpecular, domeShiny,0);
    BezierCurve semiDome = BezierCurve(semiDomeVerties, 54, domeAmbient, domeDiffusive, domeSpecular, domeShiny,0);
    BezierCurve minar = BezierCurve(minarVertices, 60, domeAmbient, domeDiffusive, domeSpecular, domeShiny,0);

    
    
    glm::vec4 cylinderAmbient = glm::vec4(0.1, 0.9, 0.1, 1.0);
    glm::vec4 cylinderDiffusive = glm::vec4(0.1, 0.9, 0.1, 1.0);
    glm::vec4 cylinderSpecular = glm::vec4(0.0, 0.9, 0.0, 1.0);
    float cylinderShiny = 12.0f;
    BezierCurve greencylinder = BezierCurve(solinoidVertices, 66, cylinderAmbient, cylinderDiffusive, cylinderSpecular, cylinderShiny,0);

    cylinderAmbient = glm::vec4(0.7, 0.3, 0.3, 1.0);
    cylinderDiffusive = glm::vec4(0.7, 0.3, 0.3, 1.0);
    cylinderSpecular = glm::vec4(0.7, 0.3, 0.3, 1.0);
    BezierCurve greycylinder = BezierCurve(solinoidVertices, 66, cylinderAmbient, cylinderDiffusive, cylinderSpecular, cylinderShiny,0);
    
    glm::vec4 treeAmbient = glm::vec4(0.0, 0.9, 0.0, 1.0);
    glm::vec4 treeDiffusive = glm::vec4(0.0, 0.9, 0.0, 1.0);
    glm::vec4 treeSpecular = glm::vec4(0.0, 1.0, 0.0, 1.0);
    float treeShiny = 12.0f;
    BezierCurve tree = BezierCurve(treeVertices, 138, treeAmbient, treeDiffusive, treeSpecular, treeShiny, 0);


    BezierCurve dome2 = BezierCurve(domeVerties, 75, domeAmbient, domeDiffusive, domeSpecular, domeShiny, 1);

    glm::vec4 octAmbient = glm::vec4(0.5, 0.5, 0.5, 1.0);
    glm::vec4 octDiffusive = glm::vec4(0.5, 0.5, 0.5, 1.0);
    glm::vec4 octSpecular = glm::vec4(0.7, 0.7, 0.7, 1.0);
    float octShiny = 32.0f;

    glm::vec4 octWhite = glm::vec4(0.7, 0.7, 0.7, 1.0);
    glm::vec4 octGrey = glm::vec4(0.7, 0.3, 0.3, 1.0);

    Octagon oct1 = Octagon(octAmbient, octDiffusive, octSpecular, octShiny);
    Octagon oct2 = Octagon(octWhite, octWhite, octWhite, octShiny);
    Octagon oct3 = Octagon(octGrey, octGrey, octGrey, octShiny);

    

    float cube_vertices[] = {
        // positions      // normals
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f
    };
    unsigned int cube_indices[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    unsigned int cubeVAO, cubeVBO, cubeEBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glGenBuffers(1, &cubeEBO);

    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);


    /*
    //bazierVAO
    bezierVAO = hollowBezier(cntrlPoints.data(), ((unsigned int)cntrlPoints.size() / 3) - 1);
    coordinates.clear();
    normals.clear();
    indices.clear();
    vertices.clear();

    bezierCylinderVAO = hollowBezier(cntrlPointsCylinder.data(), ((unsigned int)cntrlPointsCylinder.size() / 3) - 1);
    coordinates.clear();
    normals.clear();
    indices.clear();
    vertices.clear();

    AbirVAO = hollowBezier(Abir.data(), ((unsigned int)Abir.size() / 3) - 1);
    */

    //Materialistic Properties
    glm::vec3 ambient(0.2f, 0.2f, 0.2f);
    glm::vec3 diffuse(0.5f, 0.5f, 0.5f);
    glm::vec3 specular(5.0f, 5.0f, 5.0f);
    float shininess = 32.0f;

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    string diffuseMapPath = "rsz_11field_image.jpg";
    string specularMapPath = "rsz_11field_image.jpg";


    unsigned int diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Sphere sphere = Sphere(diffMap,specMap,0,0,2,1);



    Cube texcube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    Shader lightingShaderWithTexture("vertexShaderForPhongShadingWithTexture.vs", "fragmentShaderForPhongShadingWithTexture.fs");
    //Shader ourShader("vertexShader.vs", "fragmentShader.fs");

    diffuseMapPath = "rsz_1texture-grass-field.jpg";
    specularMapPath = "rsz_1texture-grass-field.jpg";


    diffMap = loadTexture(diffuseMapPath.c_str(), GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 2.0f, 2.0f);
    
    //diffuse aar spec string 
    diffuseMapPath = "sky.jpg";
    specularMapPath = "sky.jpg";


    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube texcube2 = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);


    diffuseMapPath = "BIG-BEN-LOWER-PART.bmp";
    specularMapPath = "BIG-BEN-LOWER-PART.bmp";
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP_TO_EDGE);
    specMap = loadTexture(specularMapPath.c_str(), GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP_TO_EDGE);
    Cube bigBenBaseCube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    bigBenBaseCube.setMaterialisticProperty(ambient, diffuse, specular, shininess);

    diffuseMapPath = "CASTLE_BLOCK.bmp";
    specularMapPath = "CASTLE_BLOCK.bmp";
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP_TO_EDGE);
    specMap = loadTexture(specularMapPath.c_str(), GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP_TO_EDGE);
    Cube castleblk = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    castleblk.setMaterialisticProperty(ambient, diffuse, specular, shininess);

    diffuseMapPath = "CASTLE_BLOCK_2.bmp";
    specularMapPath = "CASTLE_BLOCK_2.bmp";
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP_TO_EDGE);
    specMap = loadTexture(specularMapPath.c_str(), GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP_TO_EDGE);
    Cube castleblk2 = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    castleblk2.setMaterialisticProperty(ambient, diffuse, specular, shininess);


    diffuseMapPath = "BigBenFace.bmp";
    specularMapPath = "BigBenFace.bmp";
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube bigBenClockCube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    bigBenClockCube.setMaterialisticProperty(ambient, diffuse, specular, shininess);

    diffuseMapPath = "1st_Cube.bmp";
    specularMapPath = "1st_Cube.bmp";
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube firstCube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    firstCube.setMaterialisticProperty(ambient, diffuse, specular, shininess);


    diffuseMapPath = "2ndCube.bmp";
    specularMapPath = "2ndCube.bmp";
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube secondCube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    secondCube.setMaterialisticProperty(ambient, diffuse, specular, shininess);

    diffuseMapPath = "3rd_CUBE.bmp";
    specularMapPath = "3rd_CUBE.bmp";
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube thirdCube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    thirdCube.setMaterialisticProperty(ambient, diffuse, specular, shininess);

    diffuseMapPath = "1st_Cube.bmp";
    specularMapPath = "1st_Cube.bmp";
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube fourthCube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    fourthCube.setMaterialisticProperty(ambient, diffuse, specular, shininess);

   
    
    diffuseMapPath = "1st_cube.bmp";
    specularMapPath = "1st_cube.bmp";
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Pyramid pyramid = Pyramid(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    pyramid.setMaterialisticProperty(ambient, diffuse, specular, shininess);



    /*diffuseMapPath = "1st_Cube.bmp";
    specularMapPath = "1st_Cube.bmp";
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube skinnyCube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    skinnyCube.setMaterialisticProperty(ambient, diffuse, specular, shininess);*/


    diffuseMapPath = "1st_Cube.bmp";
    specularMapPath = "1st_Cube.bmp";
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube skinnyCube =  Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    skinnyCube.setMaterialisticProperty(ambient, diffuse, specular, shininess);


    

    //RIVER BODY - 
    diffuseMapPath = "water.bmp";
    specularMapPath = "1st_Cube.bmp";
    unsigned int watertexture = loadTexture(diffuseMapPath.c_str(), GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    
    //BRIDGE - 
    //CURVY ARCH like surface - 
    diffuseMapPath = "1st_Cube.bmp";
    unsigned int texture = loadTexture(diffuseMapPath.c_str(), GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    HalfTorus halftorus;


    //ROAD BLOCK
    diffuseMapPath = "road.png";
    specularMapPath = "road.png";
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube roadblk = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 3.0f, 3.0f);
    roadblk.setMaterialisticProperty(ambient, diffuse, specular, shininess);

    //RAILING
    diffuseMapPath = "rail.png";
    specularMapPath = "rail.png";
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube railblk = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    railblk.setMaterialisticProperty(ambient, diffuse, specular, shininess);


    //OCATGON SHAPE BESIDE ROAD;
    diffuseMapPath = "rail_blk.png";
    specularMapPath = "rail_blk.png";
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Octagon octblk = Octagon(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    octblk.setMaterialisticProperty(ambient, diffuse, specular, shininess);


    
    






    //ourShader.use();
    //lightingShader.use();

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        lightingShader.use();
        lightingShader.setVec3("viewPos", camera.Position);


        pointlight1.setUpPointLight(lightingShader);
        pointlight2.setUpPointLight(lightingShader);
        pointlight3.setUpPointLight(lightingShader);
        pointlight4.setUpPointLight(lightingShader);
        pointlight5.setUpPointLight(lightingShader);
        pointlight6.setUpPointLight(lightingShader);
        pointlight7.setUpPointLight(lightingShader);
        pointlight8.setUpPointLight(lightingShader);

        spotlight.setUpSpotLight(lightingShader);

        moonlight.setUpDirectionalLight(lightingShader);
        daylight.setUpDirectionalLight(lightingShader);


       


        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 400.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
        lightingShader.setMat4("projection", projection);
        

        // camera/view transformation
        glm::mat4 view ;
        if (birdEyeView) {
            glm::vec3 up(0.0f, 1.0f, 0.0f);
            view = glm::lookAt(birdEyePosition, birdEyeTarget, up);
        }
        else {
            view = camera.GetViewMatrix();
        }
        //glm::mat4 view = basic_camera.createViewMatrix();
        lightingShader.setMat4("view", view);


        



        // Modelling Transformation
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translate, rotate, revtranslate, alTogether, next, model, scale;
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(10, 20, 10));
        //rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        //rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        //rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1, 0.1, 0.1));
        model =  identityMatrix;
        lightingShader.setMat4("model", model);



        //scale = glm::scale(identityMatrix, glm::vec3(4.0, 4.0, 4.0));
        //dome2.drawBezierCurve(lightingShader, scale);


        //creating FIELD(MIDDLE PORTION) and FLOOR of the BIG BEN
        model = identityMatrix;
        //drawLake(cubeVAO, lightingShader, model);
        drawField(cubeVAO, lightingShader, model);
        //drawFloor(cubeVAO, lightingShader, model);
        
        rotate = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        translate = glm::translate(identityMatrix, glm::vec3(0.0, 0.0, 133.0));
        model = translate * rotate;
        //drawField(cubeVAO, lightingShader, model);


        rotate = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        translate = glm::translate(identityMatrix, glm::vec3(0.0, 0.0, 133.0));
        model = translate * rotate;
        //drawField(cubeVAO, lightingShader, model);

        //Draw BIG BEN 
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
        model = glm::scale(model, glm::vec3(6.3f, 30.0f, 5.0f)); // Tall base part
        bigBenBaseCube.drawCubeWithTexture(lightingShaderWithTexture, model);

        // Draw Big Ben Clock Part
        model = glm::translate(glm::mat4(1.0f), glm::vec3(-0.3f, 30.0f, -3.5f)); // Translate above the base 
        model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f)); // Clock part 
        bigBenClockCube.drawCubeWithTexture(lightingShaderWithTexture, model);

        /*model = glm::translate(model, glm::vec3(3.35f, 2.2f, -3.9f));
        model = glm::scale(model, glm::vec3(0.04f, -0.8f, 0.04f));
       
        drawCube(cubeVAO, ourShader, model, 0.0f,0.0f,0.0f);

        model = glm::translate(model, glm::vec3(4.6f, 2.62f, -3.5f));
        model = glm::scale(model, glm::vec3(0.04f, -0.2f, 0.04f));
        drawCube(cubeVAO, ourShader, model, 0.0f,0.0f,-.0f);*/


        
        drawClockHandsAndDials(cubeVAO, lightingShader);

        // Draw Big Ben another small cube
        //1st cube
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 37.0f, -2.5f));
        model = glm::scale(model, glm::vec3(6.3f, 2.0f, 5.0f)); // Tall base part
        firstCube.drawCubeWithTexture(lightingShaderWithTexture, model);

        //2nd cube
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.50f, 39.0f, -2.5f));
        model = glm::scale(model, glm::vec3(5.2f, 1.0f, 5.0f)); // Tall base part
        secondCube.drawCubeWithTexture(lightingShaderWithTexture, model);

        //3rd cube
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(1.0f, 40.0f, -2.5f));
        model = glm::scale(model, glm::vec3(4.1f, 1.0f, 5.0f)); // Tall base part
        secondCube.drawCubeWithTexture(lightingShaderWithTexture, model);

        //4th cube
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(1.5f, 41.0f, -2.5f));
        model = glm::scale(model, glm::vec3(3.0f, 1.0f, 5.0f)); // Tall base part
        secondCube.drawCubeWithTexture(lightingShaderWithTexture, model);

        //5th cube
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(1.5f, 42.0f, -2.5f));
        model = glm::scale(model, glm::vec3(3.0f, 2.0f, 5.0f)); // Tall base part
        thirdCube.drawCubeWithTexture(lightingShaderWithTexture, model);

        //PYRAMID
        model = glm::translate(glm::mat4(1.0f), glm::vec3(3.0f, 44.0f, 0.0f)); // Translate above the clock part 
        model = glm::scale(model, glm::vec3(1.6f, 6.0f, 2.6f)); // Pyramid shape 
        pyramid.drawPyramidWithTexture(lightingShaderWithTexture, model);

        //tall CUBE
        model = glm::translate(glm::mat4(1.0f), glm::vec3(2.95f, 52.5f, -2.5f)); // Translate above the clock part 
        model = glm::scale(model, glm::vec3(0.1f, 4.0f, 0.1f)); // Pyramid shape 
        //skinnyCube.drawCube(lightingShader, model, 1.0f, 0.87f, 0.0f);

        //THAMES RIVER

        model = identityMatrix;
        model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.5f, 5.0f)); // Translate above the clock part 
        model = glm::scale(model, glm::vec3(40.0f, 0.1f, 4.0f)); // lake shape
       // drawFrontLake(cubeVAO, lightingShader, model);


        //CASTLE RIGHT SIDE
        model = identityMatrix;
        model = glm::translate(glm::mat4(1.0f), glm::vec3(-10.0f, 0.0f, 0.0f));  
        model = glm::scale(model, glm::vec3(5.0f, 20.0f, 7.0f)); 
        castleblk.drawCubeWithTexture(lightingShaderWithTexture, model);

        //CASTLE RIGHT SIDE
        model = identityMatrix;
        model = glm::translate(glm::mat4(1.0f), glm::vec3(-10.0f, 0.0f, -20.0f));
        model = glm::scale(model, glm::vec3(5.0f, 20.0f, 7.0f));
        castleblk.drawCubeWithTexture(lightingShaderWithTexture, model);

        //CASTLE MAIN PART
        model = identityMatrix;
        model = glm::translate(glm::mat4(1.0f), glm::vec3(-10.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(-20.0f, 20.0f, 7.0f));
        castleblk2.drawCubeWithTexture(lightingShaderWithTexture, model);

        //CASTLE MAIN PART
        model = identityMatrix;
        model = glm::translate(glm::mat4(1.0f), glm::vec3(-10.0f, 0.0f, -20.0f));
        model = glm::scale(model, glm::vec3(-20.0f, 20.0f, 7.0f));
        castleblk2.drawCubeWithTexture(lightingShaderWithTexture, model);

        //CASTLE RIGHT SIDE
        model = identityMatrix;
        model = glm::translate(glm::mat4(1.0f), glm::vec3(-35.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(5.0f, 20.0f, 7.0f));
        castleblk.drawCubeWithTexture(lightingShaderWithTexture, model);

        //CASTLE RIGHT SIDE
        model = identityMatrix;
        model = glm::translate(glm::mat4(1.0f), glm::vec3(-35.0f, 0.0f, -20.0f));
        model = glm::scale(model, glm::vec3(5.0f, 20.0f, 7.0f));
        castleblk.drawCubeWithTexture(lightingShaderWithTexture, model);

        //Castle Right Fill
        model = identityMatrix;
        model = glm::translate(glm::mat4(1.0f), glm::vec3(-10.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(5.0f, 20.0f, -15.0f));
        castleblk2.drawCubeWithTexture(lightingShaderWithTexture, model);

        //Castle Right Fill
        model = identityMatrix;
        model = glm::translate(glm::mat4(1.0f), glm::vec3(-35.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(5.0f, 20.0f, -15.0f));
        castleblk2.drawCubeWithTexture(lightingShaderWithTexture, model);

        //Castle front right Pyrarmid
        //PYRAMID
        model = glm::translate(glm::mat4(1.0f), glm::vec3(-7.3f, 20.0f, 4.0f)); 
        model = glm::scale(model, glm::vec3(2.6f, 6.0f, 3.4f));  
        pyramid.drawPyramidWithTexture(lightingShaderWithTexture, model);


        model = glm::translate(glm::mat4(1.0f), glm::vec3(-7.3f, 20.0f, -17.0f));
        model = glm::scale(model, glm::vec3(2.6f, 6.0f, 3.4f));
        pyramid.drawPyramidWithTexture(lightingShaderWithTexture, model);

        model = glm::translate(glm::mat4(1.0f), glm::vec3(-32.3f, 20.0f, 4.0f));
        model = glm::scale(model, glm::vec3(2.6f, 6.0f, 3.4f));
        pyramid.drawPyramidWithTexture(lightingShaderWithTexture, model);


        model = glm::translate(glm::mat4(1.0f), glm::vec3(-32.3f, 20.0f, -17.0f));
        model = glm::scale(model, glm::vec3(2.6f, 6.0f, 3.4f));
        pyramid.drawPyramidWithTexture(lightingShaderWithTexture, model);


             // Draw RIVERR
        waterShader.use();
        waterShader.setMat4("view", view);
        waterShader.setMat4("projection", projection);
        waterShader.setFloat("time", currentFrame);

        glBindVertexArray(waterVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, watertexture);


        model = identityMatrix;
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 46.0f));
        model = glm::scale(model, glm::vec3(10.8f, 0.8f, 7.0f));
        waterShader.setMat4("model", model);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);




      

        //WestMinister bridge 
        // 
        // 
        //dome 

        model = identityMatrix;
        model = glm::translate(model, glm::vec3(14.0f, 0.0f, 27.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate 90 degrees around x-axis
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate 90 degrees around x-axis
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate 90 degrees around x-axis
        //model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate 90 degrees around x-axis
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate 90 degrees around x-axis
        model = glm::scale(model, glm::vec3(8.0f, 10.0f, 5.0f)); // Rotate 90 degrees around x-axis
        // Draw the disc
        halftorus.drawHalfTorus(lightingShaderWithTexture, texture, model);
        //roadbel.drawHalfSphereWithTexture(lightingShaderWithTexture, model);


        model = identityMatrix;
        model = glm::translate(model, glm::vec3(14.0f, 0.0f, 48.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate 90 degrees around x-axis
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate 90 degrees around x-axis
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate 90 degrees around x-axis
        //model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate 90 degrees around x-axis
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate 90 degrees around x-axis
        model = glm::scale(model, glm::vec3(8.0f, 10.0f, 5.0f)); // Rotate 90 degrees around x-axis
        // Draw the disc
        halftorus.drawHalfTorus(lightingShaderWithTexture, texture, model);

        model = identityMatrix;
        model = glm::translate(model, glm::vec3(14.0f, 0.0f, 69.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate 90 degrees around x-axis
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate 90 degrees around x-axis
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate 90 degrees around x-axis
        //model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate 90 degrees around x-axis
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate 90 degrees around z-axis
        model = glm::scale(model, glm::vec3(8.0f, 10.0f, 5.0f)); // Rotate 90 degrees around x-axis //scaling more, size less :")
        
        halftorus.drawHalfTorus(lightingShaderWithTexture, texture, model);
        

        //full road block
        model = identityMatrix;
        model = glm::translate(model, glm::vec3(10.0f, 7.0f, 14.0f));
        model = glm::scale(model, glm::vec3(8.0f, 0.5f, 67.0f));
        roadblk.drawCubeWithTexture(lightingShaderWithTexture, model);

        
        //BIGBEN side roadblock
        model = identityMatrix;
        model = glm::translate(model, glm::vec3(10.0f, 7.5f, 14.0f));
        model = glm::rotate(model, glm::radians(135.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(8.0f, 0.5f, 9.0f));

        roadblk.drawCubeWithTexture(lightingShaderWithTexture, model);

        //BIG BEN OPPOSITE  block ROAD EXTENSION
        model = identityMatrix;
        model = glm::translate(model, glm::vec3(10.0f, 0.8f, 87.0f));
        model = glm::scale(model, glm::vec3(8.0f, 0.5f, 50.0f));
        roadblk.drawCubeWithTexture(lightingShaderWithTexture, model);


        //BIGBEN opposite side roadblock
        model = identityMatrix;
        model = glm::translate(model, glm::vec3(10.0f, 7.2f, 80.68f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(8.0f, 0.5f, 9.0f));

        roadblk.drawCubeWithTexture(lightingShaderWithTexture, model);

        //BIG BEN side  block ROAD EXTENSION
        model = identityMatrix;
        model = glm::translate(model, glm::vec3(10.0f, 0.8f, -50.0f));
        model = glm::scale(model, glm::vec3(8.0f, 0.5f, 58.0f));
        roadblk.drawCubeWithTexture(lightingShaderWithTexture, model);

        //ralling
        model = identityMatrix;
        model = glm::translate(model, glm::vec3(10.0f, 10.0f, 81.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.8f, 0.2f, 9.0f));
        drawCube(cubeVAO, lightingShader, model, 0.2f, 0.2f, 0.2f);

        model = identityMatrix;
        model = glm::translate(model, glm::vec3(10.0f, 10.0f, 81.0f));
        
        model = glm::scale(model, glm::vec3(0.8f, -2.5f, 0.2f));
        drawCube(cubeVAO, lightingShader, model, 0.2f, 0.2f, 0.2f);


        

        model = identityMatrix;
        model = glm::translate(model, glm::vec3(17.2f, 10.0f, 81.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.8f, 0.2f, 9.0f));
        drawCube(cubeVAO, lightingShader, model, 0.2f, 0.2f, 0.2f);

        model = identityMatrix;
        model = glm::translate(model, glm::vec3(17.2f, 10.0f, 81.0f));

        model = glm::scale(model, glm::vec3(0.8f, -2.5f, 0.2f));
        drawCube(cubeVAO, lightingShader, model, 0.2f, 0.2f, 0.2f);


        model = identityMatrix;
        model = glm::translate(model, glm::vec3(10.0f, 10.0f, 58.6f));
        model = glm::scale(model, glm::vec3(0.8f, 0.2f, 22.33f));
        //railblk.drawCubeWithTexture(lightingShaderWithTexture, model);
        drawCube(cubeVAO, lightingShader, model, 0.2f, 0.2f, 0.2f);

        model = identityMatrix;
        model = glm::translate(model, glm::vec3(10.0f, 10.0f, 58.6f));
        model = glm::scale(model, glm::vec3(0.8f, -2.5f, 0.2f));
        //railblk.drawCubeWithTexture(lightingShaderWithTexture, model);
        drawCube(cubeVAO, lightingShader, model, 0.2f, 0.2f, 0.2f);

        model = identityMatrix;
        model = glm::translate(model, glm::vec3(10.0f, 9.3f, 58.0f));
        model = glm::scale(model, glm::vec3(1.8f, 0.5f, 1.8f));
        //railblk.drawCubeWithTexture(lightingShaderWithTexture, model);
        drawNarrowMinar(cubeVAO, minar, semiDome, oct3, oct2, lightingShaderWithTexture, model);


        model = identityMatrix;
        model = glm::translate(model, glm::vec3(9.5f, 7.0f, 58.6f));

        model = glm::scale(model, glm::vec3(1.0f, -7.0f, 1.0f));
        //railblk.drawCubeWithTexture(lightingShaderWithTexture, model);
        //drawCube(cubeVAO, lightingShader, model, 0.2f, 0.2f, 0.2f);
        octblk.drawOctagonWithTexture(lightingShaderWithTexture, model);

        model = identityMatrix;
        model = glm::translate(model, glm::vec3(17.2f, 10.0f, 58.6f));
        model = glm::scale(model, glm::vec3(0.8f, 0.2f, 22.33f));
        //railblk.drawCubeWithTexture(lightingShaderWithTexture, model);
        drawCube(cubeVAO, lightingShader, model, 0.2f, 0.2f, 0.2f);

        model = identityMatrix;
        model = glm::translate(model, glm::vec3(17.2f, 10.0f, 58.6f));
        model = glm::scale(model, glm::vec3(0.8f, -2.5f, 0.2f));
        //railblk.drawCubeWithTexture(lightingShaderWithTexture, model);
        drawCube(cubeVAO, lightingShader, model, 0.2f, 0.2f, 0.2f);

        model = identityMatrix;
        model = glm::translate(model, glm::vec3(16.0f, 7.0f, 58.6f));

        model = glm::scale(model, glm::vec3(1.0f, -7.0f, 1.0f));
        //railblk.drawCubeWithTexture(lightingShaderWithTexture, model);
        //drawCube(cubeVAO, lightingShader, model, 0.2f, 0.2f, 0.2f);
        octblk.drawOctagonWithTexture(lightingShaderWithTexture, model);


        model = identityMatrix;
        model = glm::translate(model, glm::vec3(17.0f, 9.3f, 58.0f));
        model = glm::scale(model, glm::vec3(1.8f, 0.5f, 1.8f));
        //railblk.drawCubeWithTexture(lightingShaderWithTexture, model);
        drawNarrowMinar(cubeVAO, minar, semiDome, oct3, oct2, lightingShaderWithTexture, model);


        model = identityMatrix;
        model = glm::translate(model, glm::vec3(10.0f, 10.0f, 36.0f));
        model = glm::scale(model, glm::vec3(0.8f, 0.2f, 22.33f));
        //railblk.drawCubeWithTexture(lightingShaderWithTexture, model);
        drawCube(cubeVAO, lightingShader, model, 0.2f, 0.2f, 0.2f);


       



        model = identityMatrix;
        model = glm::translate(model, glm::vec3(10.0f, 10.0f, 36.0f));
        model = glm::scale(model, glm::vec3(0.8f, -2.5f, 0.2f));
        //railblk.drawCubeWithTexture(lightingShaderWithTexture, model);
        drawCube(cubeVAO, lightingShader, model, 0.2f, 0.2f, 0.2f);

       


        model = identityMatrix;
        model = glm::translate(model, glm::vec3(9.2f, 7.0f, 36.0f));

        model = glm::scale(model, glm::vec3(1.0f, -7.0f, 1.0f));
        //railblk.drawCubeWithTexture(lightingShaderWithTexture, model);
        //drawCube(cubeVAO, lightingShader, model, 0.2f, 0.2f, 0.2f);
        octblk.drawOctagonWithTexture(lightingShaderWithTexture, model);

        model = identityMatrix;
        model = glm::translate(model, glm::vec3(9.0f, 9.3f, 35.2f));
        model = glm::scale(model, glm::vec3(1.8f, 0.5f, 1.8f));
        //railblk.drawCubeWithTexture(lightingShaderWithTexture, model);
        drawNarrowMinar(cubeVAO, minar, semiDome, oct3, oct2, lightingShaderWithTexture, model);

        model = identityMatrix;
        model = glm::translate(model, glm::vec3(17.2f, 10.0f, 36.0f));
        model = glm::scale(model, glm::vec3(0.8f, 0.2f, 22.33f));
        //railblk.drawCubeWithTexture(lightingShaderWithTexture, model);
        drawCube(cubeVAO, lightingShader, model, 0.2f, 0.2f, 0.2f);

        model = identityMatrix;
        model = glm::translate(model, glm::vec3(17.0f, 9.3f, 35.2f));
        model = glm::scale(model, glm::vec3(1.8f, 0.5f, 1.8f));
        //railblk.drawCubeWithTexture(lightingShaderWithTexture, model);
        drawNarrowMinar(cubeVAO, minar, semiDome, oct3, oct2, lightingShaderWithTexture, model);

        model = identityMatrix;
        model = glm::translate(model, glm::vec3(17.2f, 10.0f, 36.0f));
        model = glm::scale(model, glm::vec3(0.8f, -2.5f, 0.2f));
        //railblk.drawCubeWithTexture(lightingShaderWithTexture, model);
        drawCube(cubeVAO, lightingShader, model, 0.2f, 0.2f, 0.2f);

        model = identityMatrix;
        model = glm::translate(model, glm::vec3(16.0f, 7.0f, 36.0f));

        model = glm::scale(model, glm::vec3(1.0f, -7.0f, 1.0f));
        //railblk.drawCubeWithTexture(lightingShaderWithTexture, model);
        //drawCube(cubeVAO, lightingShader, model, 0.2f, 0.2f, 0.2f);
        octblk.drawOctagonWithTexture(lightingShaderWithTexture, model);

        model = identityMatrix;
        model = glm::translate(model, glm::vec3(10.0f, 10.0f, 13.34f));
        model = glm::scale(model, glm::vec3(0.8f, 0.2f, 22.33f));
        //railblk.drawCubeWithTexture(lightingShaderWithTexture, model)
        drawCube(cubeVAO, lightingShader, model, 0.2f, 0.2f, 0.2f);

        model = identityMatrix;
        model = glm::translate(model, glm::vec3(10.0f, 10.0f, 13.34f));
        model = glm::scale(model, glm::vec3(0.8f, -2.5f, 0.2f));
        //railblk.drawCubeWithTexture(lightingShaderWithTexture, model)
        drawCube(cubeVAO, lightingShader, model, 0.2f, 0.2f, 0.2f);

        model = identityMatrix;
        model = glm::translate(model, glm::vec3(17.2f, 10.0f, 13.34f));
        model = glm::scale(model, glm::vec3(0.8f, 0.2f, 22.33f));
        //railblk.drawCubeWithTexture(lightingShaderWithTexture, model)
        drawCube(cubeVAO, lightingShader, model, 0.2f, 0.2f, 0.2f);

        model = identityMatrix;
        model = glm::translate(model, glm::vec3(17.2f, 10.0f, 13.34f));
        model = glm::scale(model, glm::vec3(0.8f, -2.5f, 0.2f));
        //railblk.drawCubeWithTexture(lightingShaderWithTexture, model)
        drawCube(cubeVAO, lightingShader, model, 0.2f, 0.2f, 0.2f);

        
        model = identityMatrix;
        model = glm::translate(model, glm::vec3(10.0f, 10.0f, 13.0f));
        model = glm::rotate(model, glm::radians(135.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.8f, 0.2f, 9.0f));
        //railblk.drawCubeWithTexture(lightingShaderWithTexture, model);
        drawCube(cubeVAO, lightingShader, model, 0.2f, 0.2f, 0.2f);



        model = identityMatrix;
        model = glm::translate(model, glm::vec3(17.2f, 10.0f, 13.0f));
        model = glm::rotate(model, glm::radians(135.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.8f, 0.2f, 9.0f));
        //railblk.drawCubeWithTexture(lightingShaderWithTexture, model);
        drawCube(cubeVAO, lightingShader, model, 0.2f, 0.2f, 0.2f);

         


        

        //Tajmahal design
        translate = glm::translate(identityMatrix, glm::vec3(0.0, 2.0, -8.0));
        scale = glm::scale(identityMatrix, glm::vec3(1.0, 1.3, 1.0));
        next = scale * translate;
        //drawTajmahal(cubeVAO, lightingShader, next);
        //central dome
        translate = glm::translate(identityMatrix, glm::vec3(-3.5f, 12.0f, -24.5f));
        scale = glm::scale(identityMatrix, glm::vec3(1.0, 1.0, 1.0));
        model = next * translate * scale;
        //drawDome(cubeVAO, dome, oct2, lightingShader, model);
        //SDFL
        translate = glm::translate(identityMatrix, glm::vec3(-10.0f, 12.0f, -16.0f));
        scale = glm::scale(identityMatrix, glm::vec3(1.5, 1.5, 1.5));
        model = next * translate * scale;
        //drawSemiDome(cubeVAO, semiDome, oct2, oct2, lightingShader, model);
        //SDFR
        translate = glm::translate(identityMatrix, glm::vec3(5.0f, 12.0f, -16.0f));
        scale = glm::scale(identityMatrix, glm::vec3(1.5, 1.5, 1.5));
        model = next * translate * scale;
        //drawSemiDome(cubeVAO, semiDome, oct2, oct2, lightingShader, model);
        //SDBL
        translate = glm::translate(identityMatrix, glm::vec3(-10.0f, 12.0f, -31.5f));
        scale = glm::scale(identityMatrix, glm::vec3(1.5, 1.5, 1.5));
        model = next * translate * scale;
        //drawSemiDome(cubeVAO, semiDome, oct2, oct2, lightingShader, model);
        //SDBR
        translate = glm::translate(identityMatrix, glm::vec3(5.0f, 12.0f, -31.5f));
        scale = glm::scale(identityMatrix, glm::vec3(1.5, 1.5, 1.5));
        model = next * translate * scale;
        //drawSemiDome(cubeVAO, semiDome, oct2, oct2, lightingShader, model);




        //Minar right
        translate = glm::translate(identityMatrix, glm::vec3(17.5, 0.0, -2.5));
        model = next * translate;
        //drawMinar(cubeVAO, minar, semiDome, oct3, oct2, lightingShader, model);
        //Minar left
        translate = glm::translate(identityMatrix, glm::vec3(-22.5, 0.0, -2.5));
        model = next * translate;
        //drawMinar(cubeVAO, minar, semiDome, oct3, oct2, lightingShader, model);
        //Minar right back
        translate = glm::translate(identityMatrix, glm::vec3(17.5, 0.0, -42.5));
        model = next * translate;
        //drawMinar(cubeVAO, minar, semiDome, oct3, oct2, lightingShader, model);
        //Minar left back
        translate = glm::translate(identityMatrix, glm::vec3(-22.5, 0.0, -42.5));
        model = next * translate;
        //drawMinar(cubeVAO, minar, semiDome, oct3, oct2, lightingShader, model);

        //drawNarrowMinarTogether(cubeVAO, minar, semiDome, oct3, oct2, lightingShader, next);
        


        model = identityMatrix;
        
        drawNormalTree(tree,greycylinder,lightingShader,model);
        drawTrees(tree, greencylinder, greycylinder,lightingShader,model);



        //Drawing tree using fractiles
        translate = glm::translate(identityMatrix, glm::vec3(8.0, 0.0, 8.0));
        model = translate;
        drawTreeWithFractiles(cubeVAO, lightingShader, model, 0, 0, 0, 0);


        //Drawing tree using fractiles
        translate = glm::translate(identityMatrix, glm::vec3(8.0, 0.0, -8.0));
        model = translate;
        drawTreeWithFractiles(cubeVAO, lightingShader, model, 0, 0, 0, 0);

        //Drawing tree using fractiles
        translate = glm::translate(identityMatrix, glm::vec3(8.0, 0.0, -24.0));
        model = translate;
        drawTreeWithFractiles(cubeVAO, lightingShader, model, 0, 0, 0, 0);

        //Drawing tree using fractiles
        translate = glm::translate(identityMatrix, glm::vec3(8.0, 0.0, -40.0));
        model = translate;
        drawTreeWithFractiles(cubeVAO, lightingShader, model, 0, 0, 0, 0);


        //Drawing tree using fractiles
        translate = glm::translate(identityMatrix, glm::vec3(20.0, 0.0, 8.0));
        model = translate;
        drawTreeWithFractiles(cubeVAO, lightingShader, model, 0, 0, 0, 0);


        //Drawing tree using fractiles
        translate = glm::translate(identityMatrix, glm::vec3(20.0, 0.0, -8.0));
        model = translate;
        drawTreeWithFractiles(cubeVAO, lightingShader, model, 0, 0, 0, 0);

        //Drawing tree using fractiles
        translate = glm::translate(identityMatrix, glm::vec3(20.0, 0.0, -24.0));
        model = translate;
        drawTreeWithFractiles(cubeVAO, lightingShader, model, 0, 0, 0, 0);

        //Drawing tree using fractiles
        translate = glm::translate(identityMatrix, glm::vec3(20.0, 0.0, -40.0));
        model = translate;
        drawTreeWithFractiles(cubeVAO, lightingShader, model, 0, 0, 0, 0);
        
        


        glm::mat4 modelForSphere = glm::mat4(1.0f);
        modelForSphere = glm::translate(model, glm::vec3(1.5f, 1.2f, 0.5f));
        sphere.drawSphere(lightingShader, modelForSphere);

        // also draw the lamp object(s)
        ourShader.use();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        // we now draw as many light bulbs as we have point lights.
        glBindVertexArray(lightCubeVAO);
        for (unsigned int i = 0; i < 4; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
            ourShader.setMat4("model", model);
            ourShader.setVec3("color", glm::vec3(0.8f, 0.8f, 0.8f));
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }

        for (unsigned int i = 4; i < 8; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.1f)); // Make it a smaller cube
            ourShader.setMat4("model", model);
            ourShader.setVec3("color", glm::vec3(0.8f, 0.8f, 0.8f));
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }

        model = glm::mat4(1.0f);
        model = glm::translate(model, spotLightPosition);
        model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
        ourShader.setMat4("model", model);
        ourShader.setVec3("color", glm::vec3(0.8f, 0.8f, 0.8f));
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        lightingShaderWithTexture.use();
        lightingShaderWithTexture.setVec3("viewPos", camera.Position);

        lightingShaderWithTexture.setMat4("projection", projection);
        lightingShaderWithTexture.setMat4("view", view);

        lightingShaderWithTexture.use();

   




        pointlight1.setUpPointLight(lightingShaderWithTexture);
        pointlight2.setUpPointLight(lightingShaderWithTexture);
        pointlight3.setUpPointLight(lightingShaderWithTexture);
        pointlight4.setUpPointLight(lightingShaderWithTexture);
        pointlight5.setUpPointLight(lightingShaderWithTexture);
        pointlight6.setUpPointLight(lightingShaderWithTexture);
        pointlight7.setUpPointLight(lightingShaderWithTexture);
        pointlight8.setUpPointLight(lightingShaderWithTexture);

        spotlight.setUpSpotLight(lightingShaderWithTexture);

        moonlight.setUpDirectionalLight(lightingShaderWithTexture);
        daylight.setUpDirectionalLight(lightingShaderWithTexture);


        
        model = identityMatrix;
        lightingShaderWithTexture.setMat4("model", model);
        //drawFieldWithTexture(lightingShaderWithTexture, model);

        
        translate = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 30.0f));
        scale = glm::scale(identityMatrix, glm::vec3(90.0f, 90.0f, 90.0f));
        rotate = glm::rotate(identityMatrix, glm::radians(20.0f * 0.05f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = translate * scale;
        //sphere.drawSphereWithTexture(lightingShaderWithTexture, model);;

       




        translate = glm::translate(identityMatrix, glm::vec3(-57.0f, -5.0f, -57.0f));
        scale = glm::scale(identityMatrix, glm::vec3(114.0f, 114.0f, 1.0f));
        model = translate * scale;
        texcube.drawCubeWithTexture(lightingShaderWithTexture, model);

        translate = glm::translate(identityMatrix, glm::vec3(57.0f, -5.0f, -57.0f));
        scale = glm::scale(identityMatrix, glm::vec3(1.0f, 114.0f, 114.0f));
        model = translate * scale;
        texcube.drawCubeWithTexture(lightingShaderWithTexture, model);
        
        translate = glm::translate(identityMatrix, glm::vec3(-57.0f, -5.0f, -57.0f));
        scale = glm::scale(identityMatrix, glm::vec3(1.0f, 114.0f, 114.0f));
        model = translate * scale;
        texcube.drawCubeWithTexture(lightingShaderWithTexture, model);
        
        translate = glm::translate(identityMatrix, glm::vec3(57.0f, -5.0f, -57.0f));
        scale = glm::scale(identityMatrix, glm::vec3(1.0f, 114.0f, 114.0f));
        model = translate * scale;
        texcube.drawCubeWithTexture(lightingShaderWithTexture, model);

        translate = glm::translate(identityMatrix, glm::vec3(-57.0f, -5.0f, 57.0f));
        scale = glm::scale(identityMatrix, glm::vec3(1.0f, 114.0f, 114.0f));
        model = translate * scale;
        texcube.drawCubeWithTexture(lightingShaderWithTexture, model);

        translate = glm::translate(identityMatrix, glm::vec3(57.0f, -5.0f, 57.0f));
        scale = glm::scale(identityMatrix, glm::vec3(1.0f, 114.0f, 114.0f));
        model = translate * scale;
        texcube.drawCubeWithTexture(lightingShaderWithTexture, model);

        translate = glm::translate(identityMatrix, glm::vec3(-57.0f, -5.0f, 138.0f));
        scale = glm::scale(identityMatrix, glm::vec3(114.0f, 114.0f, 1.0f));
        model = translate * scale;
        texcube.drawCubeWithTexture(lightingShaderWithTexture, model);

        translate = glm::translate(identityMatrix, glm::vec3(-57.0f, 100.0f, -57.0f));
        scale = glm::scale(identityMatrix, glm::vec3(190.0f, 1.0f, 200.0f));
        model = translate * scale;
        texcube2.drawCubeWithTexture(lightingShaderWithTexture, model);

        glm::mat4 modelMatrixForContainer = glm::mat4(1.0f);
        modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(0.0f, 3.0f, 2.0f));
        //cube.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &cubeEBO);

    glfwTerminate();
    return 0;
}

void drawTrees(BezierCurve& NormalTree, BezierCurve& CylinderGreen, BezierCurve& CylinderGrey, Shader& lightingShader, glm::mat4 alTogether)
{

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);



    translate = glm::translate(identityMatrix, glm::vec3(8, 0.0, 86));
    model = alTogether * translate;
    drawCylindricalTree(CylinderGreen,CylinderGrey,lightingShader, model);

    translate = glm::translate(identityMatrix, glm::vec3(8, 0.0, 102));
    model = alTogether * translate;
    drawCylindricalTree(CylinderGreen, CylinderGrey, lightingShader, model);

    translate = glm::translate(identityMatrix, glm::vec3(8, 0.0, 118));
    model = alTogether *  translate;
    drawCylindricalTree(CylinderGreen, CylinderGrey, lightingShader, model);

    translate = glm::translate(identityMatrix, glm::vec3(8, 0.0, 136));
    model = alTogether *  translate;
    drawCylindricalTree(CylinderGreen, CylinderGrey, lightingShader, model);





    translate = glm::translate(identityMatrix, glm::vec3(20, 0.0,86));
    model = alTogether *  translate;
    drawCylindricalTree(CylinderGreen, CylinderGrey, lightingShader, model);

    translate = glm::translate(identityMatrix, glm::vec3(20, 0.0, 102));
    model = alTogether *  translate;
    drawCylindricalTree(CylinderGreen, CylinderGrey, lightingShader, model);

    translate = glm::translate(identityMatrix, glm::vec3(20, 0.0, 118));
    model = alTogether * translate;
    drawCylindricalTree(CylinderGreen, CylinderGrey, lightingShader, model);

    translate = glm::translate(identityMatrix, glm::vec3(20, 0.0, 136));
    model = alTogether * translate;
    drawCylindricalTree(CylinderGreen, CylinderGrey, lightingShader, model);
  



    /*translate = glm::translate(identityMatrix, glm::vec3(3.5, 0.0, 4.0));
    model = alTogether *  translate;
    drawCylindricalTree(CylinderGreen, CylinderGrey, lightingShader, model);

    translate = glm::translate(identityMatrix, glm::vec3(3.5, 0.0, 14.0));
    model = alTogether *  translate;
    drawCylindricalTree(CylinderGreen, CylinderGrey, lightingShader, model);

    translate = glm::translate(identityMatrix, glm::vec3(3.5, 0.0, 24.0));
    model = alTogether *  translate;
    drawCylindricalTree(CylinderGreen, CylinderGrey, lightingShader, model);

    translate = glm::translate(identityMatrix, glm::vec3(3.5, 0.0, 34.0));
    model = alTogether *  translate;
    drawCylindricalTree(CylinderGreen, CylinderGrey, lightingShader, model);

    translate = glm::translate(identityMatrix, glm::vec3(3.5, 0.0, 44.0));
    model = alTogether *  translate;
    drawCylindricalTree(CylinderGreen, CylinderGrey, lightingShader, model);

    translate = glm::translate(identityMatrix, glm::vec3(3.5, 0.0, 54.0));
    model = alTogether *  translate;
    drawCylindricalTree(CylinderGreen, CylinderGrey, lightingShader, model);

    translate = glm::translate(identityMatrix, glm::vec3(3.5, 0.0, 80.0));
    model = alTogether * translate;
    drawCylindricalTree(CylinderGreen, CylinderGrey, lightingShader, model);

    translate = glm::translate(identityMatrix, glm::vec3(3.5, 0.0, 90.0));
    model = alTogether * translate;
    drawCylindricalTree(CylinderGreen, CylinderGrey, lightingShader, model);

    translate = glm::translate(identityMatrix, glm::vec3(3.5, 0.0, 100.0));
    model = alTogether * translate;
    drawCylindricalTree(CylinderGreen, CylinderGrey, lightingShader, model);

    translate = glm::translate(identityMatrix, glm::vec3(3.5, 0.0, 110.0));
    model = alTogether * translate;
    drawCylindricalTree(CylinderGreen, CylinderGrey, lightingShader, model);

    translate = glm::translate(identityMatrix, glm::vec3(3.5, 0.0, 120.0));
    model = alTogether * translate;
    drawCylindricalTree(CylinderGreen, CylinderGrey, lightingShader, model);

    translate = glm::translate(identityMatrix, glm::vec3(3.5, 0.0, 130.0));
    model = alTogether * translate;
    drawCylindricalTree(CylinderGreen, CylinderGrey, lightingShader, model);*/






    //translate = glm::translate(identityMatrix, glm::vec3(-50.0, 0.0, 63.0));
    //model = alTogether * translate;
    //drawCylindricalTree(CylinderGreen, CylinderGrey, lightingShader, model);

    //translate = glm::translate(identityMatrix, glm::vec3(-40.0, 0.0, 63.0));
    //model = alTogether * translate;
    //drawCylindricalTree(CylinderGreen, CylinderGrey, lightingShader, model);

    //translate = glm::translate(identityMatrix, glm::vec3(-30.0, 0.0, 63.0));
    //model = alTogether * translate;
    //drawCylindricalTree(CylinderGreen, CylinderGrey, lightingShader, model);

    //translate = glm::translate(identityMatrix, glm::vec3(-20.0, 0.0, 63.0));
    //model = alTogether * translate;
    //drawCylindricalTree(CylinderGreen, CylinderGrey, lightingShader, model);

    //translate = glm::translate(identityMatrix, glm::vec3(-12.0, 0.0, 63.0));
    //model = alTogether * translate;
    //drawCylindricalTree(CylinderGreen, CylinderGrey, lightingShader, model);

    //translate = glm::translate(identityMatrix, glm::vec3(50.0, 0.0, 63.0));
    //model = alTogether * translate;
    //drawCylindricalTree(CylinderGreen, CylinderGrey, lightingShader, model);

    //translate = glm::translate(identityMatrix, glm::vec3(40.0, 0.0, 63.0));
    //model = alTogether * translate;
    //drawCylindricalTree(CylinderGreen, CylinderGrey, lightingShader, model);

    //translate = glm::translate(identityMatrix, glm::vec3(30.0, 0.0, 63.0));
    //model = alTogether * translate;
    //drawCylindricalTree(CylinderGreen, CylinderGrey, lightingShader, model);

    //translate = glm::translate(identityMatrix, glm::vec3(20.0, 0.0, 63.0));
    //model = alTogether * translate;
    //drawCylindricalTree(CylinderGreen, CylinderGrey, lightingShader, model);

    //translate = glm::translate(identityMatrix, glm::vec3(12.0, 0.0, 63.0));
    //model = alTogether * translate;
    //drawCylindricalTree(CylinderGreen, CylinderGrey, lightingShader, model);




    //translate = glm::translate(identityMatrix, glm::vec3(-50.0, 0.0, 70.0));
    //model = alTogether * translate;
    //drawCylindricalTree(CylinderGreen, CylinderGrey, lightingShader, model);

    //translate = glm::translate(identityMatrix, glm::vec3(-40.0, 0.0, 70.0));
    //model = alTogether * translate;
    //drawCylindricalTree(CylinderGreen, CylinderGrey, lightingShader, model);

    //translate = glm::translate(identityMatrix, glm::vec3(-30.0, 0.0, 70.0));
    //model = alTogether * translate;
    //drawCylindricalTree(CylinderGreen, CylinderGrey, lightingShader, model);

    //translate = glm::translate(identityMatrix, glm::vec3(-20.0, 0.0, 70.0));
    //model = alTogether * translate;
    //drawCylindricalTree(CylinderGreen, CylinderGrey, lightingShader, model);

    //translate = glm::translate(identityMatrix, glm::vec3(-12.0, 0.0, 70.0));
    //model = alTogether * translate;
    //drawCylindricalTree(CylinderGreen, CylinderGrey, lightingShader, model);

    //translate = glm::translate(identityMatrix, glm::vec3(50.0, 0.0, 70.0));
    //model = alTogether * translate;
    //drawCylindricalTree(CylinderGreen, CylinderGrey, lightingShader, model);

    //translate = glm::translate(identityMatrix, glm::vec3(40.0, 0.0, 70.0));
    //model = alTogether * translate;
    //drawCylindricalTree(CylinderGreen, CylinderGrey, lightingShader, model);

    //translate = glm::translate(identityMatrix, glm::vec3(30.0, 0.0, 70.0));
    //model = alTogether * translate;
    //drawCylindricalTree(CylinderGreen, CylinderGrey, lightingShader, model);

    //translate = glm::translate(identityMatrix, glm::vec3(20.0, 0.0, 70.0));
    //model = alTogether * translate;
    //drawCylindricalTree(CylinderGreen, CylinderGrey, lightingShader, model);

    //translate = glm::translate(identityMatrix, glm::vec3(12.0, 0.0, 70.0));
    //model = alTogether * translate;
    //drawCylindricalTree(CylinderGreen, CylinderGrey, lightingShader, model);







    //scale = glm::scale(identityMatrix, glm::vec3(2.0, 2.5, 2.0));

    ////right side
    //translate = glm::translate(identityMatrix, glm::vec3(19.0, 0.0, 12.0));
    //model = alTogether * translate * scale;
    //drawNormalTree(NormalTree, CylinderGrey, lightingShader, model);

    //translate = glm::translate(identityMatrix, glm::vec3(45.0, 0.0, 12.0));
    //model = alTogether * translate * scale;
    //drawNormalTree(NormalTree, CylinderGrey, lightingShader, model);

    //translate = glm::translate(identityMatrix, glm::vec3(19.0, 0.0, 45.0));
    //model = alTogether * translate * scale;
    //drawNormalTree(NormalTree, CylinderGrey, lightingShader, model);

    //translate = glm::translate(identityMatrix, glm::vec3(45.0, 0.0, 45.0));
    //model = alTogether * translate * scale;
    //drawNormalTree(NormalTree, CylinderGrey, lightingShader, model);

    //translate = glm::translate(identityMatrix, glm::vec3(19.0, 0.0, 90.0));
    //model = alTogether * translate * scale;
    //drawNormalTree(NormalTree, CylinderGrey, lightingShader, model);

    //translate = glm::translate(identityMatrix, glm::vec3(45.0, 0.0, 90.0));
    //model = alTogether * translate * scale;
    //drawNormalTree(NormalTree, CylinderGrey, lightingShader, model);

    //translate = glm::translate(identityMatrix, glm::vec3(19.0, 0.0, 120.0));
    //model = alTogether * translate * scale;
    //drawNormalTree(NormalTree, CylinderGrey, lightingShader, model);

    //translate = glm::translate(identityMatrix, glm::vec3(45.0, 0.0, 120.0));
    //model = alTogether * translate * scale;
    //drawNormalTree(NormalTree, CylinderGrey, lightingShader, model);





    ////left side
    //translate = glm::translate(identityMatrix, glm::vec3(-19.0, 0.0, 12.0));
    //model = alTogether * translate * scale;
    //drawNormalTree(NormalTree, CylinderGrey, lightingShader, model);

    //translate = glm::translate(identityMatrix, glm::vec3(-45.0, 0.0, 12.0));
    //model = alTogether * translate * scale;
    //drawNormalTree(NormalTree, CylinderGrey, lightingShader, model);

    //translate = glm::translate(identityMatrix, glm::vec3(-19.0, 0.0, 45.0));
    //model = alTogether * translate * scale;
    //drawNormalTree(NormalTree, CylinderGrey, lightingShader, model);

    //translate = glm::translate(identityMatrix, glm::vec3(-45.0, 0.0, 45.0));
    //model = alTogether * translate * scale;
    //drawNormalTree(NormalTree, CylinderGrey, lightingShader, model);

    //translate = glm::translate(identityMatrix, glm::vec3(-19.0, 0.0, 90.0));
    //model = alTogether * translate * scale;
    //drawNormalTree(NormalTree, CylinderGrey, lightingShader, model);

    //translate = glm::translate(identityMatrix, glm::vec3(-45.0, 0.0, 90.0));
    //model = alTogether * translate * scale;
    //drawNormalTree(NormalTree, CylinderGrey, lightingShader, model);

    //translate = glm::translate(identityMatrix, glm::vec3(-19.0, 0.0, 120.0));
    //model = alTogether * translate * scale;
    //drawNormalTree(NormalTree, CylinderGrey, lightingShader, model);

    //translate = glm::translate(identityMatrix, glm::vec3(-45.0, 0.0, 120.0));
    //model = alTogether * translate * scale;
    //drawNormalTree(NormalTree, CylinderGrey, lightingShader, model);

}

void drawNarrowMinar(unsigned int& cubeVAO, BezierCurve& cylinder, BezierCurve& semiDome, Octagon& base, Octagon& oct, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 scale2 = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);


    scale2 = glm::scale(identityMatrix, glm::vec3(0.15, 0.8, 0.15));


    scale = glm::scale(identityMatrix, glm::vec3(2.0, 4.0, 2.0));
    translate = glm::translate(identityMatrix, glm::vec3(0.0, -0.5, 0.0));
    model = alTogether * scale2 * scale * translate;
    //oct.drawOctagonWithMaterialisticProperty(lightingShader, model);

    scale = glm::scale(identityMatrix, glm::vec3(2.5, 9.0, 2.5));
    translate = glm::translate(identityMatrix, glm::vec3(2.4, 2.0, 2.4));
    model = alTogether * scale2 * translate * scale;
    cylinder.drawBezierCurve(lightingShader, model);

    scale = glm::scale(identityMatrix, glm::vec3(1.9, 0.3, 1.9));
    translate = glm::translate(identityMatrix, glm::vec3(0.1, 7.0, 0.1));
    model = alTogether * scale2 * translate * scale;
    //oct.drawOctagonWithMaterialisticProperty(lightingShader, model);

    scale = glm::scale(identityMatrix, glm::vec3(1.7, 0.3, 1.7));
    translate = glm::translate(identityMatrix, glm::vec3(0.3, 13.0, 0.3));
    model = alTogether * scale2 * translate * scale;
    //oct.drawOctagonWithMaterialisticProperty(lightingShader, model);

    scale2 = glm::scale(identityMatrix, glm::vec3(0.15, 0.15, 0.15));

    translate = glm::translate(identityMatrix, glm::vec3(0.6, 101.5, 0.6));
    model = alTogether * scale2 * translate;
    drawSemiDome(cubeVAO, semiDome, oct, oct, lightingShader, model);

}

void drawNarrowMinarTogether(unsigned int& cubeVAO, BezierCurve& minar, BezierCurve& semiDome, Octagon& oct3, Octagon& oct2, Shader& lightingShader, glm::mat4 next)
{

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 scale2 = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);

    //narrow minar shape
    translate = glm::translate(identityMatrix, glm::vec3(-5.6, 0.0, -6.1));
    model = next * translate;
    drawNarrowMinar(cubeVAO, minar, semiDome, oct3, oct2, lightingShader, model);


    translate = glm::translate(identityMatrix, glm::vec3(4.9, 0.0, -6.1));
    model = next * translate;
    drawNarrowMinar(cubeVAO, minar, semiDome, oct3, oct2, lightingShader, model);


    translate = glm::translate(identityMatrix, glm::vec3(-11.0, 0.0, -6.5));
    model = next * translate;
    drawNarrowMinar(cubeVAO, minar, semiDome, oct3, oct2, lightingShader, model);


    translate = glm::translate(identityMatrix, glm::vec3(10.5, 0.0, -6.5));
    model = next * translate;
    drawNarrowMinar(cubeVAO, minar, semiDome, oct3, oct2, lightingShader, model);



    translate = glm::translate(identityMatrix, glm::vec3(-15.1, 0.0, -10.6));
    model = next * translate;
    drawNarrowMinar(cubeVAO, minar, semiDome, oct3, oct2, lightingShader, model);


    translate = glm::translate(identityMatrix, glm::vec3(14.6, 0.0, -10.6));
    model = next * translate;
    drawNarrowMinar(cubeVAO, minar, semiDome, oct3, oct2, lightingShader, model);


    translate = glm::translate(identityMatrix, glm::vec3(-15.6, 0.0, -16.1));
    model = next * translate;
    drawNarrowMinar(cubeVAO, minar, semiDome, oct3, oct2, lightingShader, model);


    translate = glm::translate(identityMatrix, glm::vec3(14.9, 0.0, -16.1));
    model = next * translate;
    drawNarrowMinar(cubeVAO, minar, semiDome, oct3, oct2, lightingShader, model);


    translate = glm::translate(identityMatrix, glm::vec3(-15.6, 0.0, -26.6));
    model = next * translate;
    drawNarrowMinar(cubeVAO, minar, semiDome, oct3, oct2, lightingShader, model);


    translate = glm::translate(identityMatrix, glm::vec3(14.9, 0.0, -26.6));
    model = next * translate;
    drawNarrowMinar(cubeVAO, minar, semiDome, oct3, oct2, lightingShader, model);


    translate = glm::translate(identityMatrix, glm::vec3(-5.6, 0.0, -36.6));
    model = next * translate;
    drawNarrowMinar(cubeVAO, minar, semiDome, oct3, oct2, lightingShader, model);


    translate = glm::translate(identityMatrix, glm::vec3(4.9, 0.0, -36.6));
    model = next * translate;
    drawNarrowMinar(cubeVAO, minar, semiDome, oct3, oct2, lightingShader, model);


    translate = glm::translate(identityMatrix, glm::vec3(-11.0, 0.0, -36.1));
    model = next * translate;
    drawNarrowMinar(cubeVAO, minar, semiDome, oct3, oct2, lightingShader, model);


    translate = glm::translate(identityMatrix, glm::vec3(10.5, 0.0, -36.1));
    model = next * translate;
    drawNarrowMinar(cubeVAO, minar, semiDome, oct3, oct2, lightingShader, model);


    translate = glm::translate(identityMatrix, glm::vec3(-15.1, 0.0, -32.2));
    model = next * translate;
    drawNarrowMinar(cubeVAO, minar, semiDome, oct3, oct2, lightingShader, model);


    translate = glm::translate(identityMatrix, glm::vec3(14.6, 0.0, -32.2));
    model = next * translate;
    drawNarrowMinar(cubeVAO, minar, semiDome, oct3, oct2, lightingShader, model);


}

void drawMinar(unsigned int& cubeVAO, BezierCurve& cylinder, BezierCurve& semiDome, Octagon& base, Octagon& oct, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);


    scale = glm::scale(identityMatrix, glm::vec3(2.0, 4.0, 2.0));
    translate = glm::translate(identityMatrix, glm::vec3(0.0, -0.5, 0.0));
    model = alTogether * scale * translate;
    oct.drawOctagonWithMaterialisticProperty(lightingShader, model);

    scale = glm::scale(identityMatrix, glm::vec3(2.5, 9.0, 2.5));
    translate = glm::translate(identityMatrix, glm::vec3(2.4, 2.0, 2.4));
    model = alTogether * translate * scale;
    cylinder.drawBezierCurve(lightingShader, model);

    scale = glm::scale(identityMatrix, glm::vec3(1.9, 0.3, 1.9));
    translate = glm::translate(identityMatrix, glm::vec3(0.1, 7.0, 0.1));
    model = alTogether * translate * scale;
    oct.drawOctagonWithMaterialisticProperty(lightingShader, model);

    scale = glm::scale(identityMatrix, glm::vec3(1.7, 0.3, 1.7));
    translate = glm::translate(identityMatrix, glm::vec3(0.3, 13.0, 0.3));
    model = alTogether * translate * scale;
    oct.drawOctagonWithMaterialisticProperty(lightingShader, model);

    scale = glm::scale(identityMatrix, glm::vec3(1.0, 1.0, 1.0));
    translate = glm::translate(identityMatrix, glm::vec3(0.6, 18.5, 0.6));
    model = alTogether * translate * scale;
    drawSemiDome(cubeVAO, semiDome, oct, oct, lightingShader, model);

}


void drawCylindricalTree(BezierCurve& CylinderGreen, BezierCurve& CylinderGrey, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);



    scale = glm::scale(identityMatrix, glm::vec3(1.0, 3.0, 1.0));
    translate = glm::translate(identityMatrix, glm::vec3(0.0, 1.5, 0.0));
    model = alTogether * translate * scale;
    CylinderGreen.drawBezierCurve(lightingShader, model);

    scale = glm::scale(identityMatrix, glm::vec3(0.5, 1.0, 0.5));
    model = alTogether * scale; 
    CylinderGrey.drawBezierCurve(lightingShader, model);

}

void drawNormalTree(BezierCurve& NormalTree, BezierCurve& CylinderGrey, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);



    scale = glm::scale(identityMatrix, glm::vec3(2.0, 5.0, 2.0));
    translate = glm::translate(identityMatrix, glm::vec3(0.0, 4.0, 84.0));
    model = alTogether * translate * scale;
    NormalTree.drawBezierCurve(lightingShader, model);

    scale = glm::scale(identityMatrix, glm::vec3(1.0, 4.0, 1.0));
    translate = glm::translate(identityMatrix, glm::vec3(0.0, 0.0, 84.0));
    model = alTogether * translate * scale;
    CylinderGrey.drawBezierCurve(lightingShader, model);

    scale = glm::scale(identityMatrix, glm::vec3(2.0, 5.0, 2.0));
    translate = glm::translate(identityMatrix, glm::vec3(0.0, 4.0, 130.0));
    model = alTogether * translate * scale;
    NormalTree.drawBezierCurve(lightingShader, model);

    scale = glm::scale(identityMatrix, glm::vec3(1.0, 4.0, 1.0));
    translate = glm::translate(identityMatrix, glm::vec3(0.0, 0.0, 130.0));
    model = alTogether * translate * scale;
    CylinderGrey.drawBezierCurve(lightingShader, model);



    scale = glm::scale(identityMatrix, glm::vec3(2.0, 5.0, 2.0));
    translate = glm::translate(identityMatrix, glm::vec3(-15.0, 4.0, 84.0));
    model = alTogether * translate * scale;
    NormalTree.drawBezierCurve(lightingShader, model);

    scale = glm::scale(identityMatrix, glm::vec3(1.0, 4.0, 1.0));
    translate = glm::translate(identityMatrix, glm::vec3(-15.0, 0.0, 84.0));
    model = alTogether * translate * scale;
    CylinderGrey.drawBezierCurve(lightingShader, model);

    scale = glm::scale(identityMatrix, glm::vec3(2.0, 5.0, 2.0));
    translate = glm::translate(identityMatrix, glm::vec3(-15.0, 4.0, 130.0));
    model = alTogether * translate * scale;
    NormalTree.drawBezierCurve(lightingShader, model);

    scale = glm::scale(identityMatrix, glm::vec3(1.0, 4.0, 1.0));
    translate = glm::translate(identityMatrix, glm::vec3(-15.0, 0.0, 130.0));
    model = alTogether * translate * scale;
    CylinderGrey.drawBezierCurve(lightingShader, model);


    scale = glm::scale(identityMatrix, glm::vec3(2.0, 5.0, 2.0));
    translate = glm::translate(identityMatrix, glm::vec3(-30.0, 4.0, 84.0));
    model = alTogether * translate * scale;
    NormalTree.drawBezierCurve(lightingShader, model);

    scale = glm::scale(identityMatrix, glm::vec3(1.0, 4.0, 1.0));
    translate = glm::translate(identityMatrix, glm::vec3(-30.0, 0.0, 84.0));
    model = alTogether * translate * scale;
    CylinderGrey.drawBezierCurve(lightingShader, model);

    scale = glm::scale(identityMatrix, glm::vec3(2.0, 5.0, 2.0));
    translate = glm::translate(identityMatrix, glm::vec3(-30.0, 4.0, 130.0));
    model = alTogether * translate * scale;
    NormalTree.drawBezierCurve(lightingShader, model);

    scale = glm::scale(identityMatrix, glm::vec3(1.0, 4.0, 1.0));
    translate = glm::translate(identityMatrix, glm::vec3(-30.0, 0.0, 130.0));
    model = alTogether * translate * scale;
    CylinderGrey.drawBezierCurve(lightingShader, model);


}

void drawDome(unsigned int& cubeVAO, BezierCurve& Dome, Octagon& base, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);



    scale = glm::scale(identityMatrix, glm::vec3(4.0, 5.0, 4.0));
    translate = glm::translate(identityMatrix, glm::vec3(3.5, 1.0, 3.5));
    model = alTogether * translate * scale;
    Dome.drawBezierCurve(lightingShader, model);

    scale = glm::scale(identityMatrix, glm::vec3(3.0, 3.0, 3.0));
    model = alTogether * scale;
    base.drawOctagonWithMaterialisticProperty(lightingShader, model);

}

void drawSemiDome(unsigned int& cubeVAO, BezierCurve& semiDome, Octagon& base, Octagon& mid, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);



    scale = glm::scale(identityMatrix, glm::vec3(1.5, 2.0, 1.5));
    translate = glm::translate(identityMatrix, glm::vec3(1.8, 0.5, 1.8));
    model = alTogether * translate * scale;
    semiDome.drawBezierCurve(lightingShader, model);

    scale = glm::scale(identityMatrix, glm::vec3(1.5, 1.0, 1.5));
    model = alTogether  *  scale;
    base.drawOctagonWithMaterialisticProperty(lightingShader, model);

    scale = glm::scale(identityMatrix, glm::vec3(1.5, 0.3, 1.5));
    translate = glm::translate(identityMatrix, glm::vec3(0.0, 2.3, 0.0));
    model = alTogether * translate * scale;
    mid.drawOctagonWithMaterialisticProperty(lightingShader, model);


    scale = glm::scale(identityMatrix, glm::vec3(0.3, 1.5, 0.3));
    translate = glm::translate(identityMatrix, glm::vec3(1.1, 1.0, 0.1));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.9, 0.9, 0.9);

    scale = glm::scale(identityMatrix, glm::vec3(0.3, 1.5, 0.3));
    translate = glm::translate(identityMatrix, glm::vec3(2.2, 1.0, 0.1));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.9, 0.9, 0.9);

    scale = glm::scale(identityMatrix, glm::vec3(0.3, 1.5, 0.3));
    translate = glm::translate(identityMatrix, glm::vec3(3.2, 1.0, 1.1));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.9, 0.9, 0.9);

    scale = glm::scale(identityMatrix, glm::vec3(0.3, 1.5, 0.3));
    translate = glm::translate(identityMatrix, glm::vec3(3.2, 1.0, 2.2));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.9, 0.9, 0.9);

    scale = glm::scale(identityMatrix, glm::vec3(0.3, 1.5, 0.3));
    translate = glm::translate(identityMatrix, glm::vec3(2.2, 1.0, 3.2));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.9, 0.9, 0.9);

    scale = glm::scale(identityMatrix, glm::vec3(0.3, 1.5, 0.3));
    translate = glm::translate(identityMatrix, glm::vec3(1.1, 1.0, 3.2));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.9, 0.9, 0.9);

    scale = glm::scale(identityMatrix, glm::vec3(0.3, 1.5, 0.3));
    translate = glm::translate(identityMatrix, glm::vec3(0.1, 1.0, 1.1));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.9, 0.9, 0.9);

    scale = glm::scale(identityMatrix, glm::vec3(0.3, 1.5, 0.3));
    translate = glm::translate(identityMatrix, glm::vec3(0.1, 1.0, 2.2));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.9, 0.9, 0.9);
    
}

void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f)
{
    lightingShader.use();

    lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
    lightingShader.setVec3("material.diffuse", glm::vec3(r, g, b));
    lightingShader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    lightingShader.setFloat("material.shininess", 32.0f);

    lightingShader.setMat4("model", model);

    glBindVertexArray(cubeVAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void drawTajmahal(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);

    model = alTogether * identityMatrix;
    drawMain(cubeVAO, lightingShader, model);

    rotate = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    translate = glm::translate(identityMatrix, glm::vec3(-21.0, 0.0, -21.0));
    model = alTogether * translate * rotate;
    drawMain(cubeVAO, lightingShader, model);

    rotate = glm::rotate(identityMatrix, glm::radians(-180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    translate = glm::translate(identityMatrix, glm::vec3(0.0, 0.0, -42.0));
    model = alTogether * translate * rotate;
    drawMain(cubeVAO, lightingShader, model);

    rotate = glm::rotate(identityMatrix, glm::radians(-270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    translate = glm::translate(identityMatrix, glm::vec3(21.0, 0.0, -21.0));
    model = alTogether * translate * rotate;
    drawMain(cubeVAO, lightingShader, model);

    model = alTogether * identityMatrix;
    drawRoof(cubeVAO, lightingShader, model);

    drawBase(cubeVAO, lightingShader, model);
}

void drawFloor(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether) {
    float baseHeight = 0.2;
    float width = 113;
    float length = 55;

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f);

    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 mirror = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(width, baseHeight, length));
    translate = glm::translate(model, glm::vec3(-0.5, 0.0, -1.0));
    model = alTogether  * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.9, 0.3, 0.3);


    //left area pond
    scale = glm::scale(identityMatrix, glm::vec3(20.0, 1.0, 2.0));
    translate = glm::translate(identityMatrix, glm::vec3(-48.0, 0.0, -17.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.9, 0.1, 0.1);

    scale = glm::scale(identityMatrix, glm::vec3(20.0, 1.0, 2.0));
    translate = glm::translate(identityMatrix, glm::vec3(-48.0, 0.0, -37.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.9, 0.1, 0.1);

    scale = glm::scale(identityMatrix, glm::vec3(2.0, 1.0, 20.0));
    translate = glm::translate(identityMatrix, glm::vec3(-30.0, 0.0, -37.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.9, 0.1, 0.1);

    scale = glm::scale(identityMatrix, glm::vec3(2.0, 1.0, 20.0));
    translate = glm::translate(identityMatrix, glm::vec3(-48.0, 0.0, -37.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.9, 0.1, 0.1);

    //water
    scale = glm::scale(identityMatrix, glm::vec3(18.0, 0.6, 18.0));
    translate = glm::translate(identityMatrix, glm::vec3(-48.0, 0.0, -35.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.0, 0.7, 0.7);
    
    
    
    //right area pond
    scale = glm::scale(identityMatrix, glm::vec3(20.0, 1.0, 2.0));
    translate = glm::translate(identityMatrix, glm::vec3(28.0, 0.0, -17.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.9, 0.1, 0.1);

    scale = glm::scale(identityMatrix, glm::vec3(20.0, 1.0, 2.0));
    translate = glm::translate(identityMatrix, glm::vec3(28.0, 0.0, -37.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.9, 0.1, 0.1);

    scale = glm::scale(identityMatrix, glm::vec3(2.0, 1.0, 20.0));
    translate = glm::translate(identityMatrix, glm::vec3(28.0, 0.0, -37.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.9, 0.1, 0.1);

    scale = glm::scale(identityMatrix, glm::vec3(2.0, 1.0, 20.0));
    translate = glm::translate(identityMatrix, glm::vec3(46.0, 0.0, -37.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.9, 0.1, 0.1);

    //water
    scale = glm::scale(identityMatrix, glm::vec3(18.0, 0.6, 18.0));
    translate = glm::translate(identityMatrix, glm::vec3(30.0, 0.0, -35.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.0, 0.7, 0.7);

}

void drawRoof(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether) {
    float height = 0.5;
    float width = 21;
    float length = 29;


    float r = 0.8f;
    float g = 0.8f;
    float b = 0.8f;

    float rp = 1.0f;
    float gp = 1.0f;
    float bp = 1.0f;

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);

    //mid
    scale = glm::scale(identityMatrix, glm::vec3(width, height, length));
    translate = glm::translate(identityMatrix, glm::vec3(-0.5, 0.0, 0.0));
    translate2 = glm::translate(identityMatrix, glm::vec3(0.0, 11.0, -35.5));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.7, 0.7, 0.7);

    //l
    scale = glm::scale(identityMatrix, glm::vec3(5.0, height, 22));
    translate = glm::translate(identityMatrix, glm::vec3(-0.5, 0.0, 0.0));
    translate2 = glm::translate(identityMatrix, glm::vec3(-12.0, 11.0, -32.5));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.7, 0.7, 0.7);

    //r
    scale = glm::scale(identityMatrix, glm::vec3(5.0, height, 22));
    translate = glm::translate(identityMatrix, glm::vec3(-0.5, 0.0, 0.0));
    translate2 = glm::translate(identityMatrix, glm::vec3(12.0, 11.0, -32.5));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.7, 0.7, 0.7);

    scale = glm::scale(identityMatrix, glm::vec3(5.0, height, 20));
    translate = glm::translate(identityMatrix, glm::vec3(-0.5, 0.0, 0.0));
    translate2 = glm::translate(identityMatrix, glm::vec3(12.0, 11.0, -30.0));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.7, 0.7, 0.7);

    scale = glm::scale(identityMatrix, glm::vec3(6, height, 36));
    rotate = glm::rotate(identityMatrix, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    translate = glm::translate(identityMatrix, glm::vec3(10.5, 11.0, -36.0));
    model = alTogether  * translate * rotate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.7, 0.7, 0.7);

    scale = glm::scale(identityMatrix, glm::vec3(6, height, 36));
    rotate = glm::rotate(identityMatrix, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    translate = glm::translate(identityMatrix, glm::vec3(-14.5, 11.0, -32.0));
    model = alTogether * translate * rotate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.7, 0.7, 0.7);

}

void drawEntrance(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    float height = 9.0;
    float width = 0.5;
    float length = 4.0;


    float r = 0.8f;
    float g = 0.8f;
    float b = 0.8f;

    float rp = 1.0f;
    float gp = 1.0f;
    float bp = 0.8f;

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 mirror = glm::mat4(1.0f);

    //entrance right side 1 ERS1
    scale = glm::scale(identityMatrix, glm::vec3(width, height, length));
    translate = glm::translate(identityMatrix, glm::vec3(3.0, 2.0, -10.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, rp, gp, bp);

    //ELS1
    scale = glm::scale(identityMatrix, glm::vec3(width, height, length));
    translate = glm::translate(identityMatrix, glm::vec3(-3.5, 2.0, -10.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, rp, gp, bp);

    //ETS1
    scale = glm::scale(identityMatrix, glm::vec3(7.0f, 0.5f, length));
    translate = glm::translate(identityMatrix, glm::vec3(-3.5, 11.0, -10.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, rp, gp, bp);

    //bottom
    scale = glm::scale(identityMatrix, glm::vec3(7.0f, 0.5f, length));
    translate = glm::translate(identityMatrix, glm::vec3(-3.5, 1.5, -10.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, rp, gp, bp);

    //back
    scale = glm::scale(identityMatrix, glm::vec3(7.0f, height, 0.5));
    translate = glm::translate(identityMatrix, glm::vec3(-3.5, 2.0, -10.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, rp, gp, bp);
}

void drawSideFrame(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    float height = 9.0;
    float width = 0.5;
    float length = 0.5;

    float r = 0.8f;
    float g = 0.8f;
    float b = 0.8f;

    float rp = 1.0f;
    float gp = 1.0f;
    float bp = 1.0f;

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 mirror = glm::mat4(1.0f);

    //left window top
    scale = glm::scale(identityMatrix, glm::vec3(0.5f, 0.4f, 1.0f));
    translate = glm::translate(identityMatrix, glm::vec3(-7.75, 5.5, -0.5));
    model = alTogether * translate * scale;
    drawEntrance(cubeVAO, lightingShader, model);

    //left window bottom
    scale = glm::scale(identityMatrix, glm::vec3(0.5f, 0.4f, 1.0f));
    translate = glm::translate(identityMatrix, glm::vec3(-7.75, 1.0, -0.5));
    model = alTogether * translate * scale;
    drawEntrance(cubeVAO, lightingShader, model);

    //side right
    scale = glm::scale(identityMatrix, glm::vec3(1.0, 10.0, 0.5));
    translate = glm::translate(identityMatrix, glm::vec3(-6.0, 1.0, -6.6));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, rp, gp, bp);

    //side left
    scale = glm::scale(identityMatrix, glm::vec3(1.0, 10.0, 0.5));
    translate = glm::translate(identityMatrix, glm::vec3(-10.5, 1.0, -6.6));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, rp, gp, bp);

    //side middle
    scale = glm::scale(identityMatrix, glm::vec3(4.0, 0.8, 0.5));
    translate = glm::translate(identityMatrix, glm::vec3(-10.0, 5.5, -6.6));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, rp, gp, bp);

    //side top
    scale = glm::scale(identityMatrix, glm::vec3(4.0, 0.8, 0.5));
    translate = glm::translate(identityMatrix, glm::vec3(-10.0, 10.1, -6.6));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, rp, gp, bp);

    //border top
    scale = glm::scale(identityMatrix, glm::vec3(5.5, 1.0, 0.5));
    translate = glm::translate(identityMatrix, glm::vec3(-10.5, 10.9, -6.5));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, r, g, b);

}

void drawDoorFrame(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    float height = 9.0;
    float width = 0.5;
    float length = 1.0;

    float r = 0.8f;
    float g = 0.8f;
    float b = 0.8f;

    float rp = 1.0f;
    float gp = 1.0f;
    float bp = 1.0f;
    
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 mirror = glm::mat4(1.0f);

    //ES1
    model = alTogether;
    drawEntrance(cubeVAO, lightingShader, model);
    
    //ERS2
    scale = glm::scale(identityMatrix, glm::vec3(1.0f, 9.5f, 0.9f));
    translate = glm::translate(identityMatrix, glm::vec3(3.5, 2.0, -6.6));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, r, g, b);

    //ELS2
    scale = glm::scale(identityMatrix, glm::vec3(1.0f, 9.5f, 0.9f));
    translate = glm::translate(identityMatrix, glm::vec3(-4.5, 2.0, -6.6));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, r, g, b);

    //ETS2
    scale = glm::scale(identityMatrix, glm::vec3(9.0f, 1.0f, 0.9f));
    translate = glm::translate(identityMatrix, glm::vec3(-4.5, 11.5, -6.6));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, r, g, b);

    //ERS3
    scale = glm::scale(identityMatrix, glm::vec3(width, 10.5, length));
    translate = glm::translate(identityMatrix, glm::vec3(-5.0, 2.0, -6.5));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, rp, gp, bp);

    //ELS3
    scale = glm::scale(identityMatrix, glm::vec3(width, 10.5, length));
    translate = glm::translate(identityMatrix, glm::vec3(4.5, 2.0, -6.5));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, rp, gp, bp);

    //ETS3
    scale = glm::scale(identityMatrix, glm::vec3(10.0f, 0.5f, length));
    translate = glm::translate(identityMatrix, glm::vec3(-5.0, 12.5, -6.5));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, rp, gp, bp);

    //ETS4
    scale = glm::scale(identityMatrix, glm::vec3(10.0f, 1.0f, length));
    translate = glm::translate(identityMatrix, glm::vec3(-5.0, 13.0, -6.5));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, r, g, b);

    model = alTogether;
    drawSideFrame(cubeVAO, lightingShader, model);


    translate = glm::translate(identityMatrix, glm::vec3(15.5, 0.0, 0.0));
    model = alTogether * translate;
    drawSideFrame(cubeVAO, lightingShader, model);

    
}

void drawMain(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 revtranslate = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);

    //front
    drawDoorFrame(cubeVAO, lightingShader, alTogether);
    
    //rotate = glm::rotate(identityMatrix, glm::radians(45), glm::vec3(0.0f, .0f, 0.0f));
    rotate = glm::rotate(identityMatrix, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    translate = glm::translate(identityMatrix, glm::vec3(7.5,0.0, 0.0));
    revtranslate = glm::translate(identityMatrix, glm::vec3(-17.0, 0.0, -3.5));
    model = alTogether * revtranslate * rotate * translate;
    drawSideFrame(cubeVAO, lightingShader, model);

}

void drawFieldWithTexture(Shader& lightingShader, glm::mat4 alTogether)
{
    float baseHeight = 1.0f;
    float width = 110.0f;
    float length = 180.0f;

    string diffuseMapPath = "rsz_11texture-grass-field.jpg";
    string specularMapPath = "rsz_11texture-grass-field.jpg";


    unsigned int diffMap = loadTexture(diffuseMapPath.c_str(), GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap = loadTexture(specularMapPath.c_str(), GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 mirror = glm::mat4(1.0f);

    scale = glm::scale(identityMatrix, glm::vec3(width, 0.0f, length));
    translate = glm::translate(identityMatrix, glm::vec3(-52.0f, 0.0f, -40.0f));
    model = alTogether * translate * scale;
    //drawCube(cubeVAO, lightingShader, model, 0.5, 1.0, 0.0);
    cube.drawCubeWithTexture(lightingShader, model);


    scale = glm::scale(identityMatrix, glm::vec3(width, baseHeight, length));
    translate = glm::translate(identityMatrix, glm::vec3(-4.5, 0, 0.0));
    model = alTogether * translate * scale;
    //drawCube(cubeVAO, lightingShader, model, 0.5, 1.0, 0.0);
    //cube.drawCubeWithTexture(lightingShader, model);

}

void drawField(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    float baseHeight = 1.0f;
    float width = 110.0f;
    float length = 180.0f;



    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 mirror = glm::mat4(1.0f);

    scale = glm::scale(identityMatrix, glm::vec3(width, 0.0f, length));
    translate = glm::translate(identityMatrix, glm::vec3(-52.0f, 0.0f, -40.0f));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.5, 1.0, 0.0);
    //cube.drawCubeWithTexture(lightingShader, model);


    scale = glm::scale(identityMatrix, glm::vec3(width, baseHeight, length));
    translate = glm::translate(identityMatrix, glm::vec3(-4.5, 0, 0.0));
    model = alTogether * translate * scale;
    //drawCube(cubeVAO, lightingShader, model, 0.5, 1.0, 0.0);
    //cube.drawCubeWithTexture(lightingShader, model);

}

void drawFrontLake(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    float baseHeight = 0.3;
    float width = 1;
    float length = 20;

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 mirror = glm::mat4(1.0f);

    //edges
    scale = glm::scale(identityMatrix, glm::vec3(width, baseHeight, length));
    translate = glm::translate(identityMatrix, glm::vec3(1.5, 0.0, 0.0));
    model = alTogether * translate * scale;
    //drawCube(cubeVAO, lightingShader, model, 1.0, 0.2, 0.2);

    scale = glm::scale(identityMatrix, glm::vec3(width, baseHeight, length));
    translate = glm::translate(identityMatrix, glm::vec3(-2.5, 0.0, 0.0));
    model = alTogether * translate * scale;
    //drawCube(cubeVAO, lightingShader, model, 1.0, 0.2, 0.2);

    //edge front
    translate = glm::translate(identityMatrix, glm::vec3(-1.5, 0.0, 0.0));
    scale = glm::scale(identityMatrix, glm::vec3(3.0, baseHeight, 1.0));
    model = alTogether * translate * scale ;
    //drawCube(cubeVAO, lightingShader, model, 1.0, 0.2, 0.2);

    //water
    translate = glm::translate(identityMatrix, glm::vec3(-1.5, 0.0, 4.0));
    scale = glm::scale(identityMatrix, glm::vec3(3.0, 0.1, length));
    model = alTogether * translate * scale ;
    drawCube(cubeVAO, lightingShader, model, 0.149, 0.4, 0.586886);

}

void drawLake(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);


    model = identityMatrix;
    drawFrontLake(cubeVAO, lightingShader, model);

    //left lake
    scale = glm::scale(identityMatrix, glm::vec3(1.0, 1.0, 0.81));
    rotate = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    translate = glm::translate(identityMatrix, glm::vec3(-56.5, 0.0, 66.5));
    model = translate * rotate * scale;
    drawFrontLake(cubeVAO, lightingShader, model);

    //right lake
    scale = glm::scale(identityMatrix, glm::vec3(1.0, 1.0, 0.81));
    rotate = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    translate = glm::translate(identityMatrix, glm::vec3(56.5, 0.0, 66.5));
    model = translate * rotate * scale;
    drawFrontLake(cubeVAO, lightingShader, model);

    //front opposite
    scale = glm::scale(identityMatrix, glm::vec3(1.0, 1.0, -1.0));
    translate = glm::translate(identityMatrix, glm::vec3(0.0, 0.0, 133.0));
    model = translate * scale;
    drawFrontLake(cubeVAO, lightingShader, model);


    //center square
    scale = glm::scale(identityMatrix, glm::vec3(8.0, 0.8, 3.0));
    translate = glm::translate(identityMatrix, glm::vec3(-4.0, 0.0, 60.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.8, 0.8, 0.8);

    scale = glm::scale(identityMatrix, glm::vec3(8.0, 0.8, 3.0));
    translate = glm::translate(identityMatrix, glm::vec3(-4.0, 0.0, 70.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.8, 0.8, 0.8);

    scale = glm::scale(identityMatrix, glm::vec3(3.0, 0.8, 13.0));
    translate = glm::translate(identityMatrix, glm::vec3(-6.5, 0.0, 60.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.8, 0.8, 0.8);

    scale = glm::scale(identityMatrix, glm::vec3(3.0, 0.8, 13.0));
    translate = glm::translate(identityMatrix, glm::vec3(4.0, 0.0, 60.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.8, 0.8, 0.8);


    //inner edges
    scale = glm::scale(identityMatrix, glm::vec3(21.0, 0.3, 1.0));
    translate = glm::translate(identityMatrix, glm::vec3(-10.5, 0.0, 56.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 1.0, 0.2, 0.2);

    scale = glm::scale(identityMatrix, glm::vec3(1.0, 0.3, 21.0));
    translate = glm::translate(identityMatrix, glm::vec3(-10.5, 0.0, 56.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 1.0, 0.2, 0.2);

    scale = glm::scale(identityMatrix, glm::vec3(1.0, 0.3, 21.0));
    translate = glm::translate(identityMatrix, glm::vec3(9.5, 0.0, 56.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 1.0, 0.2, 0.2);

    scale = glm::scale(identityMatrix, glm::vec3(21.0, 0.3, 1.0));
    translate = glm::translate(identityMatrix, glm::vec3(-10.5, 0.0, 76.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 1.0, 0.2, 0.2);



    //center water
    scale = glm::scale(identityMatrix, glm::vec3(19.0, 0.2, 19.0));
    translate = glm::translate(identityMatrix, glm::vec3(-9.5, 0.0, 57.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.2, 1.0, 1.0);
}

void drawBase(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    float baseHeight = 4.0;
    float width = 20;
    float length = -40;

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f);



    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 mirror = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(width, baseHeight, length));
    translate = glm::translate(model, glm::vec3(0.0, -0.5, 0.0));
    model = alTogether  * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.7, 0.7, 0.7);

    mirror = glm::scale(identityMatrix, glm::vec3(-1.0, 1.0, 1.0));
    model = mirror * model;
    drawCube(cubeVAO, lightingShader, model, 0.7, 0.7, 0.7);
}


void drawTreeWithFractiles(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float L, float H, float W, int N)
{
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 next = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);



    if (N == 0) {
        float length = 0.5;
        float height = 4.0;
        float width = 0.5;

        float mvx = length * 0.05;
        float mvy = height - height * 0.1;
        float mvz = width * 0.05;


        translate = glm::translate(identityMatrix, glm::vec3(mvx, mvy, mvz));
        next = translate * alTogether;


        scale = glm::scale(identityMatrix, glm::vec3(length, height, width));
        model = alTogether * scale;
        drawCube(cubeVAO, lightingShader, model, 0.0, 0.95, 0.95);
        drawTreeWithFractiles(cubeVAO, lightingShader, next, length, height, width, N + 1);
    }

    else if (N > 0 && N < 3) {
        float length = L * 0.6;
        float height = H * 0.6;
        float width = W * 0.6;

        scale = glm::scale(identityMatrix, glm::vec3(length, height, width));
        rotate = glm::rotate(identityMatrix, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model = alTogether * rotate * scale ;
        drawCube(cubeVAO, lightingShader, model, 0.0, 0.95, 0.95);

        scale = glm::scale(identityMatrix, glm::vec3(length, height, width));
        rotate = glm::rotate(identityMatrix, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = alTogether * rotate * scale;
        drawCube(cubeVAO, lightingShader, model, 0.0, 0.95, 0.95);

        scale = glm::scale(identityMatrix, glm::vec3(length, height, width));
        rotate = glm::rotate(identityMatrix, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model = alTogether * rotate * scale;
        drawCube(cubeVAO, lightingShader, model, 0.0, 0.95, 0.95);

        scale = glm::scale(identityMatrix, glm::vec3(length, height, width));
        rotate = glm::rotate(identityMatrix, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = alTogether * rotate * scale;
        drawCube(cubeVAO, lightingShader, model, 0.0, 0.95, 0.95);

        scale = glm::scale(identityMatrix, glm::vec3(length, height, width));
        model = alTogether * scale;
        drawCube(cubeVAO, lightingShader, model, 0.0, 0.95, 0.95);
        

        float mvx = length * 0.3 + height * 0.7071;
        float mvy = height * 0.7071;
        float mvz = width * 0.3;
        translate = glm::translate(identityMatrix, glm::vec3(mvx, mvy, mvz));
        next = translate * alTogether;
        drawTreeWithFractiles(cubeVAO, lightingShader, next, length, height, width, N + 1);


        mvx = length * 0.3 ;
        mvy = height * 0.7071;
        mvz = width * 0.3 - height * 0.7071;
        translate = glm::translate(identityMatrix, glm::vec3(mvx, mvy, mvz));
        next = translate * alTogether;
        drawTreeWithFractiles(cubeVAO, lightingShader, next, length, height, width, N + 1);


        mvx = length * 0.3 - height * 0.7071;
        mvy = height * 0.7071;
        mvz = width * 0.3;
        translate = glm::translate(identityMatrix, glm::vec3(mvx, mvy, mvz));
        next = translate * alTogether;
        drawTreeWithFractiles(cubeVAO, lightingShader, next, length, height, width, N + 1);


        mvx = length * 0.3;
        mvy = height * 0.7071;
        mvz = width * 0.3 + height * 0.7071;
        translate = glm::translate(identityMatrix, glm::vec3(mvx, mvy, mvz));
        next = translate * alTogether;
        drawTreeWithFractiles(cubeVAO, lightingShader, next, length, height, width, N + 1);

        mvx = length * 0.3;
        mvy = height;
        mvz = width * 0.3 ;
        translate = glm::translate(identityMatrix, glm::vec3(mvx, mvy, mvz));
        next = translate * alTogether;
        drawTreeWithFractiles(cubeVAO, lightingShader, next, length, height, width, N + 1);
    }

    else if (N == 3) {
        float length = L * 0.6;
        float height = H * 0.6;
        float width = W * 0.6;

        scale = glm::scale(identityMatrix, glm::vec3(length, height, width));
        rotate = glm::rotate(identityMatrix, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model = alTogether * rotate * scale;
        drawCube(cubeVAO, lightingShader, model, 0.0, 0.95, 0.1);

        scale = glm::scale(identityMatrix, glm::vec3(length, height, width));
        rotate = glm::rotate(identityMatrix, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = alTogether * rotate * scale;
        drawCube(cubeVAO, lightingShader, model, 0.0, 0.95, 0.1);

        scale = glm::scale(identityMatrix, glm::vec3(length, height, width));
        rotate = glm::rotate(identityMatrix, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model = alTogether * rotate * scale;
        drawCube(cubeVAO, lightingShader, model, 0.0, 0.95, 0.1);

        scale = glm::scale(identityMatrix, glm::vec3(length, height, width));
        rotate = glm::rotate(identityMatrix, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = alTogether * rotate * scale;
        drawCube(cubeVAO, lightingShader, model, 0.0, 0.95, 0.1);

        scale = glm::scale(identityMatrix, glm::vec3(length, height, width));
        model = alTogether * scale;
        drawCube(cubeVAO, lightingShader, model, 0.0, 0.95, 0.1);
    }
    
}

void updateClockHandAngles(float& hourAngle, float& minuteAngle)
{
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm parts;
    localtime_s(&parts, &now_c);

    // Calculate the angles (in degrees) for the hour and minute hands
    minuteAngle = parts.tm_min * 6.0f; // 360 degrees / 60 minutes = 6 degrees per minute
    hourAngle = parts.tm_hour * 30.0f + parts.tm_min * 0.5f; // 360 degrees / 12 hours = 30 degrees per hour, + minute effect
}

// Function to draw the clock hands
// Function to draw the clock hands
void drawClockHandsAndDials(unsigned int cubeVAO, Shader& ourShader)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 model = identityMatrix;

    float hourAngle, minuteAngle;
    updateClockHandAngles(hourAngle, minuteAngle);

    // Draw hour hand
    model = glm::translate(identityMatrix, glm::vec3(3.0f, 30.5f, 3.5f)); // Translate above the base
    model = glm::rotate(model, glm::radians(hourAngle), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate according to hour
    model = glm::scale(model, glm::vec3(0.2f, 3.2f, 0.2f)); // Clock part
    drawCube(cubeVAO, ourShader, model, 0.0f, 0.2f, 0.2f);

    // Draw minute hand
    model = glm::translate(identityMatrix, glm::vec3(3.0f, 33.5f, 3.5f)); // Translate above the base
    model = glm::rotate(model, glm::radians(minuteAngle), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate according to minute
    model = glm::scale(model, glm::vec3(2.5f, 0.2f, 0.2f)); // Clock part
    drawCube(cubeVAO, ourShader, model, 0.0f, 0.2f, 0.2f);

    // Draw dial cubes
    // Left dial
    model = glm::translate(identityMatrix, glm::vec3(2.5f, 31.5f, 3.0f)); // Position relative to clock face
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f)); // Small cube for dial
    drawCube(cubeVAO, ourShader, model, 0.3f, 0.3f, 0.3f);

    // Right dial
    model = glm::translate(identityMatrix, glm::vec3(3.5f, 31.5f, 3.0f)); // Position relative to clock face
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f)); // Small cube for dial
    drawCube(cubeVAO, ourShader, model, 0.3f, 0.3f, 0.3f);
}






// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        if(!birdEyeView)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        if (!birdEyeView)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        if (!birdEyeView)
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        if (!birdEyeView)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        if (!birdEyeView)
            camera.ProcessKeyboard(UP, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        if (!birdEyeView)
            camera.ProcessKeyboard(DOWN, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
        if (!birdEyeView)
            camera.ProcessKeyboard(P_UP, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
        if (!birdEyeView)
            camera.ProcessKeyboard(P_DOWN, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        if (!birdEyeView)
            camera.ProcessKeyboard(Y_LEFT, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
        if (!birdEyeView)
            camera.ProcessKeyboard(Y_RIGHT, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
        if (!birdEyeView)
            camera.ProcessKeyboard(R_LEFT, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
        if (!birdEyeView)
            camera.ProcessKeyboard(R_RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
        birdEyeView = !birdEyeView;
    }
    if (birdEyeView) {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            birdEyePosition.z -= birdEyeSpeed * deltaTime; // Move forward along Z
            birdEyeTarget.z -= birdEyeSpeed * deltaTime;
            if (birdEyePosition.z <= 2.0) {
                birdEyePosition.z = 2.0;
            }
            if (birdEyeTarget.z <= -4.0) {
                birdEyeTarget.z = -4.0;
            }
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            birdEyePosition.z += birdEyeSpeed * deltaTime; // Move backward along Z
            birdEyeTarget.z += birdEyeSpeed * deltaTime;
            if (birdEyePosition.z >= 20.5) {
                birdEyePosition.z = 20.5;
            }
            if (birdEyeTarget.z >= 7.5) {
                birdEyeTarget.z = 7.5;
            }
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            birdEyePosition.x -= birdEyeSpeed * deltaTime; // Move backward along x
            birdEyeTarget.z -= birdEyeSpeed * deltaTime;
            if (birdEyePosition.z <= 2.0) {
                birdEyePosition.z = 2.0;
            }
            if (birdEyeTarget.z <= -4.0) {
                birdEyeTarget.z = -4.0;
            }
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            birdEyePosition.x += birdEyeSpeed * deltaTime; // Move forward along x
            birdEyeTarget.z += birdEyeSpeed * deltaTime;
            if (birdEyePosition.z <= 2.0) {
                birdEyePosition.z = 2.0;
            }
            if (birdEyeTarget.z <= -4.0) {
                birdEyeTarget.z = -4.0;
            }
        }
    }
    // Toggle car movement
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        isCarMoving = true;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        isCarMoving = false;

    // Toggle boat movement
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        isBoatMoving = true;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        isBoatMoving = false;
} 

void updatePositions(float deltaTime)
{
    if (isCarMoving)
        carZPosition += carSpeed * deltaTime;
    if (isBoatMoving)
        boatXPosition += boatSpeed * deltaTime;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_1 && action == GLFW_PRESS)
    {
        if (pointLightOn)
        {
            pointlight1.turnOff();
            pointlight2.turnOff();
            pointlight3.turnOff();
            pointlight4.turnOff();
            pointlight5.turnOff();
            pointlight6.turnOff();
            pointlight7.turnOff();
            pointlight8.turnOff();
            pointLightOn = !pointLightOn;
        }
        else
        {
            pointlight1.turnOn();
            pointlight2.turnOn();
            pointlight3.turnOn();
            pointlight4.turnOn();
            pointlight5.turnOn();
            pointlight6.turnOn();
            pointlight7.turnOn();
            pointlight8.turnOn();
            pointLightOn = !pointLightOn;
        }
    }


    else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        if (specularToggle)
        {

            pointlight1.turnSpecularOff();
            pointlight2.turnSpecularOff();
            pointlight3.turnSpecularOff();
            pointlight4.turnSpecularOff();
            pointlight5.turnSpecularOff();
            pointlight6.turnSpecularOff();
            pointlight7.turnSpecularOff();
            pointlight8.turnSpecularOff();

            specularToggle = !specularToggle;
        }
        else
        {

            pointlight1.turnSpecularOn();
            pointlight2.turnSpecularOn();
            pointlight3.turnSpecularOn();
            pointlight4.turnSpecularOn();
            pointlight5.turnSpecularOn();
            pointlight6.turnSpecularOn();
            pointlight7.turnSpecularOn();
            pointlight8.turnSpecularOn();
            specularToggle = !specularToggle;
        }
    }

    else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        if (diffuseToggle)
        {

            pointlight1.turnDiffuseOff();
            pointlight2.turnDiffuseOff();
            pointlight3.turnDiffuseOff();
            pointlight4.turnDiffuseOff();
            pointlight5.turnDiffuseOff();
            pointlight6.turnDiffuseOff();
            pointlight7.turnDiffuseOff();
            pointlight8.turnDiffuseOff();
            diffuseToggle = !diffuseToggle;
        }
        else
        {

            pointlight1.turnDiffuseOn();
            pointlight2.turnDiffuseOn();
            pointlight3.turnDiffuseOn();
            pointlight4.turnDiffuseOn();
            pointlight5.turnDiffuseOn();
            pointlight6.turnDiffuseOn();
            pointlight7.turnDiffuseOn();
            pointlight8.turnDiffuseOn();
            diffuseToggle = !diffuseToggle;
        }
    }

    else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
    {
        if (ambientToggle)
        {

            pointlight1.turnAmbientOff();
            pointlight2.turnAmbientOff();
            pointlight3.turnAmbientOff();
            pointlight4.turnAmbientOff();
            pointlight5.turnAmbientOff();
            pointlight6.turnAmbientOff();
            pointlight7.turnAmbientOff();
            pointlight8.turnAmbientOff();
            ambientToggle = !ambientToggle;
        }
        else
        {

            pointlight1.turnAmbientOn();
            pointlight2.turnAmbientOn();
            pointlight3.turnAmbientOn();
            pointlight4.turnAmbientOn();
            pointlight5.turnAmbientOn();
            pointlight6.turnAmbientOn();
            pointlight7.turnAmbientOn();
            pointlight8.turnAmbientOn();
            ambientToggle = !ambientToggle;
        }
    }

    else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
    {
        if (spotLightOn)
        {

            spotlight.turnOff();
            spotLightOn = !spotLightOn;
        }
        else
        {
            spotlight.turnOn();
            spotLightOn = !spotLightOn;
        }
    }

    else if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
    {
        if (dayLightOn)
        {

            daylight.turnOff();
            dayLightOn = false;
        }
        else
        {
            daylight.turnOn();
            dayLightOn = true;
        }
    }

    else if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
    {
        if (moonLightOn)
        {

            moonlight.turnOff();
            moonLightOn = !moonLightOn;
        }
        else
        {
            moonlight.turnOn();
            moonLightOn = !moonLightOn;
        }
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax)
{
    
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format = GL_RGB;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrappingModeS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrappingModeT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilteringModeMin);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilteringModeMax);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
