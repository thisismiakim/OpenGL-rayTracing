#ifdef __APPLE__
/* Defined before OpenGL and GLUT includes to avoid deprecation messages */
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif


#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <GLFW/glfw3.h>




#include "SDLFunctions.h"
#include "color.h"
#include "graphic.h"
#include "object.h"
#include "app.h"
#include "graphicFunctions.h"
#include "appFunctions.h"



int main(int argc, char *argv[])
{
    // glfw test code
    GLFWwindow* window;

    /* init the library*/
    if (!glfwInit())
        return -1;
    
    /* create a windowed mode window and its OpenGL Context*/
    window = glfwCreateWindow(640, 380, "Hello World", NULL, NULL);
    if (!window){
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current*/
    glfwMakeContextCurrent(window);

    /* loop until the user closes the window*/
    while (!glfwWindowShouldClose(window)){
        /*render here*/
        glClear(GL_COLOR_BUFFER_BIT);
        /*swap front and back buffers*/
        glfwSwapBuffers(window);
        /*poll for and process evenets*/
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;






    // if (InitApp() == false) 
    // {   
    //     ShutdownApp();
    //     return EXIT_FAILURE;
    // }

    // // Draw loop
    // SDL_Event event;
    // bool running = true;

    // while(running){
    //     ClearScreen(app.render);

    //     // Check and process I/O events
    //     // key events
    //     if (SDL_PollEvent(&event))
    //     {
    //         switch (event.type)// 
    //         {
    //             case SDL_KEYDOWN:
    //             {
    //                 running = event.key.keysym.scancode != SDL_SCANCODE_ESCAPE;
    //                 break;
    //             }
    //             case SDL_QUIT:
    //             {
    //                 running = false;
    //                 break;
    //             }
    //             default: 
    //                 break;
    //         }
    //     }

    //     // Draw the new content on the renderer
    //     DrawSquare(app.square.xpos, app.square.ypos);
        


    //     // Update the screen with the content rendered in the background buffer
    //     SDL_RenderPresent(app.render);

    // }

    // ShutdownApp();
    return EXIT_SUCCESS;
}

