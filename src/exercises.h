#ifndef EXERCISES_H
#define EXERCISES_H
#include <stdint.h>
// Exercise 1
void draw_grid(uint32_t color,uint8_t cellSize);

// exercise 2
/// pos x, pos y, width , height , color
void draw_rect(int x,int y, int width, int height, uint32_t color);

#endif