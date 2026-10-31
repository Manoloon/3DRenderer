#include <SDL2/sdl.h>
#include <stdbool.h>
#include "window.h"
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
bool is_app_running = false;

void process_input(void)
{

}

void process_render(void)
{

}

void update(void)
{

}

int main(int argc, char* args[])
{
    is_app_running = init_window(window,renderer);
 
    while(is_app_running)
    {
        process_input();
        update();
        process_render();
    }
    destroy_window(window,renderer);
    return 0;
}