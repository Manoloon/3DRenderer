#ifndef GLOBALS_H
#define GLOBALS_H
#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdbool.h>
#include "vector.h"

#define FPS 60
#define FRAME_TARGET_TIME (1000/FPS)

// TODO : all of these to config ini file
extern bool is_app_running;
extern int is_fullScreen;
extern uint32_t window_width;
extern uint32_t window_height;
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern uint32_t* color_buffer;
extern SDL_Texture* color_buffer_texture;
#endif