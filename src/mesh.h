#ifndef MESH_H
#define MESH_H
#include "vector.h"
#include "dynamicArray.h"
#include "triangle.h"

// Mesh and vertices
// TODO : this goes dead
#define N_MESH_VERTICES 8
// TODO : Implement dynarray 
extern vec3_t mesh_vertices[N_MESH_VERTICES];
extern vec3_t mesh_rotation;
// TODO : This goes dead too
#define N_MESH_FACES (6*2) // 6 cube faces * 2 triangle per face
// TODO : implement dynarray
extern face_t mesh_faces[N_MESH_FACES];

void create_mesh(void);
void update_mesh(float delta_time,vec2_t position,float FOV, vec3_t rot_speed,vec3_t camera);
void draw_mesh(void);

#endif
