#ifndef MESH_H
#define MESH_H
#include "vector.h"
#include "dynamicArray.h"
#include "triangle.h"

// DEMO CUBE
#define N_CUBE_VERTICES 8
#define N_CUBE_FACES 12
extern vec3_t cube_vertices[N_CUBE_VERTICES];
extern vec3_t cube_rotation;
extern face_t cube_faces[N_CUBE_FACES];
///////////////////////////////////////////////////////////////

typedef struct
{
    vec3_t* vertices; // TODO : dynamic array
    face_t* faces; // TODO : dynamic array
    vec3_t rotation;
}mesh_t;

extern mesh_t mesh;

void load_cube_data(void);
void create_mesh(void);
void update_mesh(float delta_time,vec2_t position,float FOV, vec3_t rot_speed,vec3_t camera);
void draw_mesh(void);

#endif
