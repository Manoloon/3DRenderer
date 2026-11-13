#include "globals.h"

bool is_app_running = false;
int is_fullScreen = false;
uint32_t window_width = 640;
uint32_t window_height = 480;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
uint32_t* color_buffer = NULL;
SDL_Texture* color_buffer_texture = NULL;
