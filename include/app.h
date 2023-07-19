#ifndef APP_H_
#define APP_H_

#include <iostream>
#include <SDL2/SDL.h>
#include "graphic.h"
#include "object.h"

// Application
struct App
{
    SDL_Window* window;
    SDL_Renderer* render;

    Graphics::Screen screen;

    Square square
    {32,
     32,
     screen.center_xpos, 
     screen.center_ypos 
    };

}app;


#endif 