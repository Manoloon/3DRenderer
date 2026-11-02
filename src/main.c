#include <SDL2/sdl.h>
#include "display.h"
#include "exercises.h"
#include "globals.h"
#include "vector.h"

#define N_POINTS 9*9*9
vec3_t cube[N_POINTS];

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

    // cube
    int point_count =0;
    for(float x = -1.0; x <= 1; x +=0.25)
    {
        for(float y = -1.0; y <= 1; y +=0.25)
        {
            for(float z = -1.0; z <= 1; z +=0.25)
            {
                vec3_t new_point={x,y,z};
                cube[point_count++] = new_point;
            }
        }
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