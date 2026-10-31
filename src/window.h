#ifndef WINDOW_H
#define WINDOW_H
#include <SDL2/SDL.h> 
#include <stdio.h>
#include "constants.h"
#include "globals.h"

bool init_window()
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
    {
        fprintf(stderr,"Error init SDL\n");
        return false;
    }
    window = SDL_CreateWindow(NULL,
                        SDL_WINDOWPOS_CENTERED,
                        SDL_WINDOWPOS_CENTERED,
                        SCREEN_W,
                        SCREEN_H,
                        SDL_WINDOW_RESIZABLE);
    if(window == NULL)
    {
        fprintf(stderr,"Window not created\n");
        return false;
    }
    renderer = SDL_CreateRenderer(window,-1,0);
    if(renderer == NULL)
    {
        fprintf(stderr,"Failed to create renderer\n");
        return false;
    }
    return true;
}

void destroy_window()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
#endif