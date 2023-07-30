#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>

/* include header files */
#include "Trace.h"
#include "RGB.h"
#include "Shader.h"



void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);


// Global Variables
// window setting global variables
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 800;

Point intersect, tmp1, tmp2, cam, point, center[4]; // 3차원 좌표
RGB color, shade, obj[4]; // RGB 색상
Vec3 dir, normal, vec; // 3차원 벡터
//Phong ps[4]; // phong shading
//Sphere3D spheres[4]; // 구체 3차원
//Ray3D ray, shadow; // 광선

// Image processing matrix
unsigned char image[SCREEN_HEIGHT][SCREEN_WIDTH][3];




// shader input

/* main loop */
int main()
{
    // Initialise GLFW 
    glfwInit();
    // Setting Up OpenGL context version to 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // MacOS option
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    /* Create a window using GLFW */ 
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, 
                                          SCREEN_HEIGHT, 
                                          "RayTracing", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "[ERROR] Failed to create GLFW window." << std::endl;
        glfwTerminate();
        return -1;
    }
    // Set the current context to the window
    glfwMakeContextCurrent(window);
    // Set callback function for resizing the window
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);



    /* Initialise GLAD.*/
    // GLAD library manages function pointers for OpenGL, handling OS-specific quirks
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "[ERROR] Failed to initialize GLAD" << std::endl;
        return -1;
    }



    /* Shader Program build and compile */



    /* Render Loop */
    while (!glfwWindowShouldClose(window))
    {
        // Process user input
        processInput(window);

        // Render the screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // 컬러값 지정해서 넣기
        glClear(GL_COLOR_BUFFER_BIT);

        // ----------------------------------------------------------------------------
        // Drawing Functions here ...

 
        
        // -------------------------------------------------------------------------------
        // Swap the buffers and poll I/O events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up Shaders

    // Terminate GLFW
    glfwTerminate();
    return 0;
}


// ----------- key event ----------------------
// 사용자 입력 처리: GLFW가 해당 프레임에서 관련 키가 눌림/해제됐는지 쿼리하고 그에 따라 반응
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: 창의 크기가 변경될 때 (OS 또는 사용자 리사이즈에 의해) 이 콜백 함수 실행
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}