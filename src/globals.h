#ifndef GLOBALS_H
#define GLOBALS_H
#include <stdint.h>
// TODO : all of these to config ini file
bool is_app_running = false;
bool is_fullScreen = false;
uint32_t window_width = DEFAULT_SCREEN_W;
uint32_t window_height = DEFAULT_SCREEN_H;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
uint32_t* color_buffer = NULL;
SDL_Texture* color_buffer_texture = NULL;
#endif