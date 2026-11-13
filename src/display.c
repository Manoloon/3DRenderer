#include "display.h"
#include "globals.h"
#include <SDL2/SDL.h>

bool init_window()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
    {
        fprintf(stderr, "Error init SDL\n");
        return false;
    }

    setFullScreen();

    window = SDL_CreateWindow(NULL,
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              window_width,
                              window_height,
                              SDL_WINDOW_RESIZABLE);
    if (window == NULL)
    {
        fprintf(stderr, "Window not created\n");
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL)
    {
        fprintf(stderr, "Failed to create renderer\n");
        return false;
    }
    if (is_fullScreen)
    {
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    }
    return true;
}

vec2_t project2D(float FOV,vec3_t points) 
{
    vec2_t projected ={(points.x * FOV)/points.z,(points.y * FOV)/points.z};
    return projected;
}

void draw_pixel(int x, int y, uint32_t color)
{
    if(x > window_width || x < 0 || y > window_height || y < 0)
    {
        return;
    }
    color_buffer[(window_width * y) + x] = color;
}

void draw_rect(int x, int y, int width, int height, uint32_t color)
{
    if(x > window_width || x < 0) return;
    if(y > window_height || y < 0) return;
    int currentX =0;
    for(int currentY=0; currentY < height; currentY++)
    {
        while(currentX < width)
        {
            draw_pixel(currentX+x,currentY+y,color);
            currentX++;
        }
        currentX = 0;
    }
}

void draw_grid(uint32_t color, uint8_t cellSize)
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

void draw_line_DDA(int x1, int y1, int x2, int y2, uint32_t color)
{
    int delta_x = x2 - x1;
    int delta_y = y2 - y1;

    int x_max_length = abs(delta_x) >= abs(delta_y) ? abs(delta_x) : abs(delta_y);
    float x_inc = delta_x / (float) x_max_length;
    float y_inc = delta_y / (float) x_max_length;

    float current_x = x1;
    float current_y = y1;
    for( int i = 0; i < x_max_length; i++)
    {
        draw_pixel((int)round(current_x),(int)round(current_y),color);
        current_x += x_inc;
        current_y += y_inc;
    }
}


void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, uint32_t color)
{
    draw_line_DDA(x1, y1, x2, y2, color);
    draw_line_DDA(x2, y2, x3, y3, color);
    draw_line_DDA(x3,y3,x1, y1, color);
}

void clearColorBuffer(uint32_t color)
{
    for (int y = 0; y < window_height; y++)
    {
        for (int x = 0; x < window_width; x++)
        {
            color_buffer[(window_width * y) + x] = color;
        }
    }
}

void updateColorBuffer()
{
    SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer, (int)window_width * (int)window_height);
    SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void renderColorBuffer()
{
    SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer, window_width * sizeof(uint32_t));
    SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void setFullScreen(void)
{
    SDL_DisplayMode display_mode;
    if (is_fullScreen)
    {
        SDL_GetCurrentDisplayMode(0, &display_mode);
        window_width = display_mode.w;
        window_height = display_mode.h;
    }
}

void destroy_window()
{
    free(color_buffer);
    SDL_DestroyTexture(color_buffer_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}