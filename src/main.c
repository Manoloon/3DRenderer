#include <SDL2/sdl.h>
#include <stdbool.h>
#include "window.h"
#include "colorBuffer.h"
#include "globals.h"


// remember 0xFFEE1100 -> 0xAA-RR-GG-BB
bool begin_play()
{
    color_buffer = (uint32_t*)malloc(sizeof(uint32_t) * window_width * window_height);
    if(color_buffer == NULL)
    {
        fprintf(stderr,"Failed to allocate memory for the color buffer\n");
        return false;
    }
    color_buffer_texture = SDL_CreateTexture(renderer,
                                SDL_PIXELFORMAT_ARGB8888,
                                SDL_TEXTUREACCESS_STREAMING,
                                window_width,window_height);
    if(color_buffer_texture == NULL)
    {
        fprintf(stderr,"FAILED to construct the color buffer texture\n");
        return false;
    }
    return true;
}

void process_input(void)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            is_app_running = false;
            break;
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_ESCAPE)
            {
                is_app_running = false;
            }
            break;
        default:
            break;
        }
    }
}
void draw_grid(uint32_t color,uint8_t cellSize)
{
    if(cellSize < 1) return;
    for(int y = 0; y < window_height;y++)
    {
        for(int x = 0; x < window_width;x++)
        {
            if(x%cellSize == 0 || y%cellSize == 0)
            {
                color_buffer[(window_width * y) + x] = color;
            }
        }
    }
}

void draw(void)
{
    SDL_SetRenderDrawColor(renderer,64,64,64,255);
    SDL_RenderClear(renderer);

    renderColorBuffer();
    clearColorBuffer(0xFF111111);
    draw_grid(0xFFFFFF00,32);
    SDL_RenderPresent(renderer);
}

void update()
{
    //updateColorBuffer();
}

int main(int argc, char* args[])
{
    is_app_running = init_window();
    if(!begin_play())
    {
        is_app_running = false;
    }

    while(is_app_running)
    {
        process_input();
        update();
        draw();
    }
    destroy_window();
    return 0;
}