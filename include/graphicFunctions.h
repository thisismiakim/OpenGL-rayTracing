#ifndef GRAPHIC_FUNCTIONS_H_
#define GRAPHIC_FUNCTIONS_H_

#include <iostream>
#include <SDL2/SDL.h>

#include "SDLFunctions.h"
#include "color.h"
#include "graphic.h"
#include "object.h"
#include "app.h"
#include "graphicFunctions.h"
#include "appFunctions.h"



// Clearing Renderer
// : erasing everything that on the render and painting it all the pixels with a predefined colors
// : it runs every frame before we actually draw a new state to the renderer
static void ClearScreen(SDL_Renderer* renderer){
    // set color
    SDL_SetRenderDrawColor(renderer, Colors::BLACK.r, Colors::BLACK.g, Colors::BLACK.b,Colors::BLACK.a);
    // select renderer
    SDL_RenderClear(renderer);
}


// Drawing Function
void DrawSquare(int x, int y)
{
    SDL_Rect rect;
    rect.x = x - (app.square.WIDTH /2);
    rect.y = y - (app.square.HEIGHT /2);
    rect.w = app.square.WIDTH;
    rect.h = app.square.HEIGHT;

    // Define the green color on the renderer
    SDL_SetRenderDrawColor(app.render, Colors::GREEN.r, Colors::GREEN.g, Colors::GREEN.b, Colors::GREEN.a);
    // Ask the renderer to fill the rect with the green color
    SDL_RenderFillRect(app.render, &rect);
}


#endif