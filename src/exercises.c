#include "exercises.h"
#include "globals.h"

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
void draw_pixel(int x, int y, uint32_t color)
{
    if(x > window_width || x < 0 || y > window_height || y < 0)
    {
        fprintf(stderr,"x and y must be lesser than window Width and height respectible and greater than 0");
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
