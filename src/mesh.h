#ifndef MESH_H
#define MESH_H
#include "vector.h"
#include "triangle.h"
#include "dynamicArray.h"
// DEMO CUBE
#define N_CUBE_VERTICES 8
#define N_CUBE_FACES 12
extern vec3_t cube_vertices[N_CUBE_VERTICES];
//extern vec3_t cube_rotation;
extern face_t cube_faces[N_CUBE_FACES];
///////////////////////////////////////////////////////////////

typedef struct
{
    dynarray_t* vertices;
    dynarray_t* faces;
    vec3_t rotation;
}mesh_t;

extern mesh_t mesh;

void load_cube_data(void);
void create_mesh(void);
void update_mesh(vec2_t position,float FOV, vec3_t rot_speed,vec3_t camera);
void draw_mesh(void);

#endif
