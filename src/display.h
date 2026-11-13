#ifndef DISPLAY_H
#define DISPLAY_H
#include <stdbool.h>
#include <stdint.h>
#include "vector.h"

bool init_window();
void destroy_window();

// tools
vec2_t project2D(float FOV, vec3_t points);
void draw_grid(uint32_t color,uint8_t cellSize);
void draw_pixel(int x, int y, uint32_t color);
void draw_line_DDA(int x1,int y1, int x2,int y2,uint32_t color);
void draw_triangle(int x1, int y1, int x2, int y2,int x3,int y3,uint32_t color);
void draw_rect(int x,int y, int width, int height, uint32_t color);
// color buffer
void clearColorBuffer(uint32_t color);
void updateColorBuffer(void);
void renderColorBuffer(void);
void setFullScreen(void);
#endif