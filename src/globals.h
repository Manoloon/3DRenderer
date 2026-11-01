#ifndef GLOBALS_H
#define GLOBALS_H
#include <stdint.h>

bool is_app_running = false;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
uint32_t* color_buffer = NULL;
SDL_Texture* color_buffer_texture = NULL;
#endif