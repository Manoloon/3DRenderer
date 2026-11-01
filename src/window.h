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

    SDL_DisplayMode display_mode;
    if(is_fullScreen)
    {
        SDL_GetCurrentDisplayMode(0,&display_mode);
        window_width = display_mode.w;
        window_height = display_mode.h;
    }

    window = SDL_CreateWindow(NULL,
                        SDL_WINDOWPOS_CENTERED,
                        SDL_WINDOWPOS_CENTERED,
                        window_width,
                        window_height,
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
    if(is_fullScreen)
    {
        SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN);
    }
    return true;
}

void destroy_window()
{
    free(color_buffer);
    SDL_DestroyTexture(color_buffer_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
#endif