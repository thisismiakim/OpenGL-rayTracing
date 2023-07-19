#ifndef COLOR_H_
#define COLOR_H_

#include <iostream>
#include <SDL2/SDL.h>

namespace Colors{
    SDL_Color BLACK = {0, 0, 0, SDL_ALPHA_OPAQUE};
    SDL_Color WHITE = {255, 255, 255, SDL_ALPHA_OPAQUE};
    SDL_Color RED = {255, 0, 0, SDL_ALPHA_OPAQUE};
    SDL_Color GREEN = {0, 255, 0, SDL_ALPHA_OPAQUE};
    SDL_Color BLUE = {0, 0, 255, SDL_ALPHA_OPAQUE};
}

#endif