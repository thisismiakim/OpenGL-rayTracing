#include <iostream>
#include <SDL2/SDL.h>

// Graphics
const int WINDOW_WIDTH = 512;
const int WINDOW_HEIGHT = 284;
SDL_Window* g_main_window;
SDL_Renderer* g_main_renderer;

// Colors
namespace Colors{
    SDL_Color BLACK = {0, 0, 0, SDL_ALPHA_OPAQUE};
}


//SDL Initialization Function
static bool Init(){
    if (SDL_Init(SDL_INIT_EVERYTHING) > 0 ){
        std::cout << "SDL_Init failed with error: "<< SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    g_main_window = SDL_CreateWindow(
        "SDL WindowTitle",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_OPENGL
    );

    if(g_main_window == nullptr){
        std::cout << "Unable to create the main window. Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return EXIT_FAILURE;
    }

    g_main_renderer = SDL_CreateRenderer(g_main_window, -1, SDL_RENDERER_PRESENTVSYNC);

    return true;
}

// Shutdown Function, Clean Up
void Shutdown(){
    if (g_main_window != nullptr){
        SDL_DestroyWindow(g_main_window);
        g_main_window = nullptr;
    }

    if (g_main_renderer != nullptr){
        SDL_DestroyRenderer(g_main_renderer);
        g_main_renderer = nullptr;
    }

    SDL_Quit();
}

// Clearing Renderer
// erasing everything that on the render and painting it all the pixels with a predefined colors
// it runs every frame before we actually draw a new state to the renderer
static void ClearScreen(SDL_Renderer* renderer){
    // set color
    SDL_SetRenderDrawColor(renderer, Colors::BLACK.r, Colors::BLACK.g, Colors::BLACK.b,Colors::BLACK.a);
    // select renderer
    SDL_RenderClear(renderer);
}

/* -----------------------------------------------------------------------*/
// Main loop
int main()
{
    if (Init() == false) {Shutdown();}

    // Draw loop
    SDL_Event event;
    bool running = true;

    while(running){
        ClearScreen(g_main_renderer);

        // Check and process I/O events
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

        // Update the screen with the content rendered in the background buffer
        SDL_RenderPresent(g_main_renderer);

    }

    Shutdown();
    return EXIT_SUCCESS;
}

