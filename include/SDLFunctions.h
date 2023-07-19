#ifndef SDL_FUNCTIONS_H_
#define SDL_FUNCTIONS_H_

#include <iostream>
#include <SDL2/SDL.h>

bool InitSDL()
{    
    if (SDL_Init(SDL_INIT_EVERYTHING) > 0 ){
        std::cout << "SDL_Init failed with error: "<< SDL_GetError() << std::endl;
        return false;
    }
    return true;
    
}


#endif