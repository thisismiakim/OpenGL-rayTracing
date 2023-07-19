#ifndef APP_FUNCTIONS_H_
#define APP_FUNCTIONS_H_

#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "SDLFunctions.h"
#include "color.h"
#include "graphic.h"
#include "object.h"
#include "app.h"
#include "graphicFunctions.h"


void ShutdownApp(){
    if (app.window != nullptr){
        SDL_DestroyWindow(app.window);
        app.window = nullptr;
    }

    if (app.render != nullptr){
        SDL_DestroyRenderer(app.render);
        app.render = nullptr;
    }

    SDL_Quit();
}


static bool InitApp(){

    if (InitSDL() == false){
        ShutdownApp();
        return false;
    }

    app.window = SDL_CreateWindow(
        "SDL WindowTitle",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        app.screen.WIDTH,
        app.screen.HEIGHT,
        SDL_WINDOW_OPENGL
    );

    if(app.window == nullptr){
        std::cout << "Unable to create the main window. Error: " << SDL_GetError() << std::endl;
        ShutdownApp();
        return false;
    }

    app.render = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_PRESENTVSYNC);

    return true;
}

#endif