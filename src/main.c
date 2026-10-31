#include <SDL2/sdl.h>
#include <stdbool.h>
#include "window.h"
#include "globals.h"

void begin_play(void)
{

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
    SDL_SetRenderDrawColor(renderer,255,64,164,255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void update(void)
{

}

int main(int argc, char* args[])
{
    is_app_running = init_window();
    begin_play();

    while(is_app_running)
    {
        process_input();
        update();
        draw();
    }
    destroy_window();
    return 0;
}