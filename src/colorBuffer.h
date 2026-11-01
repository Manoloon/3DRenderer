#ifndef COLORBUFFER_H
#define COLORBUFFER_H
#include <stdint.h>
#include <SDL2/sdl.h>
#include "constants.h"
#include "globals.h"
void clearColorBuffer(uint32_t color)
{
    for(int y = 0; y < SCREEN_H; y++)
    {
        for(int x = 0; x < SCREEN_W;x++)
        {
            color_buffer[(SCREEN_W * y) + x] = color;
        }
    }
}

void updateColorBuffer()
{
    SDL_UpdateTexture(color_buffer_texture,
                    NULL,
                    color_buffer,
                    (int)SCREEN_W * (int)SCREEN_H);
    SDL_RenderCopy(renderer,color_buffer_texture,NULL,NULL);
}

void renderColorBuffer()
{
    SDL_UpdateTexture(color_buffer_texture,
                        NULL,
                        color_buffer,
                        SCREEN_W * sizeof(uint32_t));
    SDL_RenderCopy(renderer,
                    color_buffer_texture,
                    NULL,
                    NULL);
}
#endif