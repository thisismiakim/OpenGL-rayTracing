#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "SDLFunctions.h"
#include "color.h"
#include "graphic.h"
#include "object.h"
#include "app.h"
#include "graphicFunctions.h"
#include "appFunctions.h"



int main(int argc, char *argv[])
{
    if (InitApp() == false) 
    {   
        ShutdownApp();
        return EXIT_FAILURE;
    }

    // Draw loop
    SDL_Event event;
    bool running = true;

    while(running){
        ClearScreen(app.render);

        // Check and process I/O events
        // key events
        if (SDL_PollEvent(&event))
        {
            switch (event.type)// 
            {
                case SDL_KEYDOWN:
                {
                    running = event.key.keysym.scancode != SDL_SCANCODE_ESCAPE;
                    break;
                }
                case SDL_QUIT:
                {
                    running = false;
                    break;
                }
                default: 
                    break;
            }
        }

        // Draw the new content on the renderer
        DrawSquare(app.square.xpos, app.square.ypos);
        


        // Update the screen with the content rendered in the background buffer
        SDL_RenderPresent(app.render);

    }

    ShutdownApp();
    return EXIT_SUCCESS;
}

