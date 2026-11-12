#include "mesh.h"
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

face_t mesh_faces[N_MESH_FACES]=
{
    // front
    {.a = 1, .b = 2, .c = 3},
    {.a = 1, .b = 3, .c = 4},
    // right
    {.a = 4, .b = 3, .c = 5},
    {.a = 4, .b = 5, .c = 6},
    // back
    {.a = 6, .b = 5, .c = 7},
    {.a = 6, .b = 7, .c = 8},
    // left
    {.a = 8, .b = 7, .c = 2},
    {.a = 8, .b = 2, .c = 1},
    // top
    {.a = 2, .b = 7, .c = 5},
    {.a = 2, .b = 5, .c = 3},
    // botton
    {.a = 6, .b = 8, .c = 1},
    {.a = 6, .b = 1, .c = 4}
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
        face_vertices[0] = mesh_vertices[current_face.a -1]; 
        face_vertices[1] = mesh_vertices[current_face.b -1]; 
        face_vertices[2] = mesh_vertices[current_face.c -1];

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
        draw_rect(triangle.points[0].x,triangle.points[0].y,3,3,0xFF00FFFF);
        draw_rect(triangle.points[1].x,triangle.points[1].y,3,3,0xFF00FFFF);
        draw_rect(triangle.points[2].x,triangle.points[2].y,3,3,0xFF00FFFF);
        draw_line_DDA(
                triangle.points[0].x,
                triangle.points[0].y,
                triangle.points[1].x,
                triangle.points[1].y,
                0xFFFF0000);
        draw_line_DDA(
                triangle.points[1].x,
                triangle.points[1].y,
                triangle.points[2].x,
                triangle.points[2].y,
                0xFFFF0000);
        draw_line_DDA(
                triangle.points[2].x,
                triangle.points[2].y,
                triangle.points[0].x,
                triangle.points[0].y,
                0xFFFF0000);
    }
}

void draw_line_DDA(int x1, int y1, int x2, int y2, uint32_t color)
{
    int delta_x = x2 - x1;
    int delta_y = y2 - y1;

    int x_length = abs(delta_x) >= abs(delta_y) ? abs(delta_x) : abs(delta_y);
    float x_inc = delta_x / (float) x_length;
    float y_inc = delta_y / (float) x_length;

    int current_x = x1;
    int current_y = y1;
    for( int i = 0; i < delta_x; i++)
    {
        draw_pixel((int)round(current_x),(int)round(current_y),color);
        current_x += x_inc;
        current_y += y_inc;
    }
}
