#ifndef EXERCISES_H
#define EXERCISES_H
#include <stdint.h>
#include "vector.h"
// Exercise 1
void draw_grid(uint32_t color,uint8_t cellSize);

// exercise 2
/// pos x, pos y, width , height , color
void draw_rect(int x,int y, int width, int height, uint32_t color);
vec2_t project2D(float FOV, vec3_t points);

// vertex cube
#define N_POINTS 9*9*9
extern vec3_t cube[N_POINTS];
extern vec2_t projected_points[N_POINTS];
extern vec3_t obj_rotation;
void create_vertex_cube(void);
void draw_vertex_cube(void);
void update_vertex_cube(float FOV, vec3_t rot_speed,vec3_t camera);
#endif