#ifndef GUI_H
#define GUI_H
#include <SDL2/sdl.h>
#include <stdbool.h>

struct nk_context;

bool gui_init(SDL_Window* window,SDL_Renderer* renderer);
void gui_process_event(SDL_Event* event);
void gui_begin(void);
void gui_build(void);
void gui_end(void);
void gui_shutdown(void);

struct nk_context* gui_get_context(void);
#endif