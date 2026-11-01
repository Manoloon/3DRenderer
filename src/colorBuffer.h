#ifndef COLORBUFFER_H
#define COLORBUFFER_H
#include <stdint.h>
#include <SDL2/sdl.h>
#include "constants.h"
#include "globals.h"
void clearColorBuffer(uint32_t color)
{
    for(int y = 0; y < window_height; y++)
    {
        for(int x = 0; x < window_width;x++)
        {
            color_buffer[(window_width * y) + x] = color;
        }
    }
}

void updateColorBuffer()
{
    SDL_UpdateTexture(color_buffer_texture,
                    NULL,
                    color_buffer,
                    (int)window_width * (int)window_height);
    SDL_RenderCopy(renderer,color_buffer_texture,NULL,NULL);
}

void renderColorBuffer()
{
    SDL_UpdateTexture(color_buffer_texture,
                        NULL,
                        color_buffer,
                        window_width * sizeof(uint32_t));
    SDL_RenderCopy(renderer,
                    color_buffer_texture,
                    NULL,
                    NULL);
}
#endif