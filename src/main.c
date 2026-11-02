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
// Exercise 1
void draw_grid(uint32_t color,uint8_t cellSize)
{
    if(cellSize < 1) return;
    int x = 0;
    for(int y = 0; y < window_height;y+=cellSize)
    {
        while(x < window_width)
        {
            color_buffer[(window_width * y) + x] = color;
            x+=cellSize;
        }
        x=0;
    }
}
// exercise 2
/// pos x, pos y, width , height , color
void draw_rect(int x,int y, int width, int height, uint32_t color)
{
    if(x > window_width || x < 0) return;
    if(y > window_height || y < 0) return;
    int xOffset =0;
    for(int yOffset=0; yOffset < height; yOffset++)
    {
        while(xOffset < width)
        {
            color_buffer[(window_width * (yOffset+y)) + (xOffset+x)] = color;
            xOffset++;
        }
        xOffset = 0;
    }
}

void draw(void)
{
    SDL_SetRenderDrawColor(renderer,64,64,64,255);
    SDL_RenderClear(renderer);
    draw_grid(0xFFFFFF00,8);
    draw_rect(10,60,100,120,0xFF0000FF);
    draw_rect(100,10,60,120,0xFFFF0000);
    draw_rect(120,100,100,20,0xFF00FF00);
    renderColorBuffer();

    clearColorBuffer(0xFF000000);
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