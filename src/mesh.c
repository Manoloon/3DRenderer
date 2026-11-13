#include "mesh.h"
#include "display.h"
#include "exercises.h"
#include "triangle.h"
#include "globals.h"

vec3_t mesh_rotation = {0.0,0.0,0.0};
vec3_t mesh_vertices[N_MESH_VERTICES]=
{
    {.x = -1, .y = -1, .z = -1}, // 1
    {.x = -1, .y =  1, .z = -1}, // 2
    {.x =  1, .y =  1, .z = -1}, // 3
    {.x =  1, .y = -1, .z = -1}, // 4
    {.x =  1, .y =  1, .z =  1}, // 5
    {.x =  1, .y = -1, .z =  1}, // 6
    {.x = -1, .y =  1, .z =  1}, // 7
    {.x = -1, .y = -1, .z =  1}, // 8
};

// the numbers are the index .. maybe should start with 0;
face_t mesh_faces[N_MESH_FACES]=
{
    // front
    {.a = 0, .b = 1, .c = 2},
    {.a = 0, .b = 2, .c = 3},
    // right
    {.a = 3, .b = 2, .c = 4},
    {.a = 3, .b = 4, .c = 5},
    // back
    {.a = 5, .b = 4, .c = 6},
    {.a = 5, .b = 6, .c = 7},
    // left
    {.a = 7, .b = 6, .c = 1},
    {.a = 7, .b = 1, .c = 0},
    // top
    {.a = 1, .b = 6, .c = 4},
    {.a = 1, .b = 4, .c = 2},
    // botton
    {.a = 5, .b = 7, .c = 0},
    {.a = 5, .b = 0, .c = 3}
};
triangle_t triangles_to_render[N_MESH_FACES];
void create_mesh(void)
{

}
void update_mesh(float delta_time,vec2_t position,float FOV, vec3_t rot_speed,vec3_t camera)
{
    mesh_rotation.x += rot_speed.x;
    mesh_rotation.y += rot_speed.y;
    mesh_rotation.z += rot_speed.z;

    for(int i = 0; i < N_MESH_FACES;i++)
    {
        face_t current_face = mesh_faces[i];
        vec3_t face_vertices[3];

        face_vertices[0] = mesh_vertices[current_face.a]; 
        face_vertices[1] = mesh_vertices[current_face.b]; 
        face_vertices[2] = mesh_vertices[current_face.c];

        triangle_t projected_triangle;
        
        for(int j = 0; j < 3;j++)
        {
            vec3_t transform_vertex = face_vertices[j];
            transform_vertex = vec3_rotate_x(transform_vertex,mesh_rotation.x);
            transform_vertex = vec3_rotate_y(transform_vertex,mesh_rotation.y);
            transform_vertex = vec3_rotate_z(transform_vertex,mesh_rotation.z);
            transform_vertex.z -= camera.z;
            vec2_t projected_point = project2D(FOV,transform_vertex);
            projected_point.x += position.x;
            projected_point.y += position.y;
            projected_triangle.points[j] = projected_point;
        }
        triangles_to_render[i] = projected_triangle;
    }
}

void draw_mesh(void) 
{
    for(int i = 0; i < N_MESH_FACES;i++)
    {
        triangle_t triangle = triangles_to_render[i];
        draw_rect(triangle.points[0].x,triangle.points[0].y,10,10,0xFFFF0000);
        draw_rect(triangle.points[1].x,triangle.points[1].y,5,5,0xFFFF00FF);
        draw_rect(triangle.points[2].x,triangle.points[2].y,3,3,0xFF00FFFF);
        draw_triangle(triangle.points[0].x,triangle.points[0].y,
                        triangle.points[1].x,triangle.points[1].y,
                        triangle.points[2].x,triangle.points[2].y,0xFFFF0000);
    }
}
