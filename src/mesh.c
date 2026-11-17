#include "mesh.h"
#include "display.h"
#include "exercises.h"
#include "triangle.h"
#include "globals.h"

mesh_t mesh =
    {
        .vertices = NULL,
        .faces = NULL,
        .rotation = {0.0,0.0,0.0}
    };

vec3_t cube_rotation = {0.0,0.0,0.0};
vec3_t cube_vertices[N_CUBE_VERTICES]=
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
face_t cube_faces[N_CUBE_FACES]=
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
dynarray_t* triangles_to_render = NULL;
void load_cube_data(void)
{
    for(int i = 0; i < N_CUBE_VERTICES; i++)
    {
        vec3_t cube_vertex = cube_vertices[i];
        // TODO : dyn_push(mesh.vertices,cube_vertex)
    }
    for(int i = 0; i < N_CUBE_FACES;i++)
    {
        face_t cube_face = cube_faces[i];
        // TODO : dyn_push(mesh.faces,cube_face);
    }
}
void create_mesh(void)
{
    triangles_to_render = dynArray_create(sizeof(triangle_t));
}
void update_mesh(float delta_time,vec2_t position,float FOV, vec3_t rot_speed,vec3_t camera)
{
    cube_rotation.x += rot_speed.x;
    cube_rotation.y += rot_speed.y;
    cube_rotation.z += rot_speed.z;
    for(int i = 0; i < N_CUBE_FACES;i++)
    {
        face_t current_face = cube_faces[i];
        vec3_t face_vertices[3];

        face_vertices[0] = cube_vertices[current_face.a]; 
        face_vertices[1] = cube_vertices[current_face.b]; 
        face_vertices[2] = cube_vertices[current_face.c];

        triangle_t projected_triangle;
        
        for(int j = 0; j < 3;j++)
        {
            vec3_t transform_vertex = face_vertices[j];
            transform_vertex = vec3_rotate_x(transform_vertex,cube_rotation.x);
            transform_vertex = vec3_rotate_y(transform_vertex,cube_rotation.y);
            transform_vertex = vec3_rotate_z(transform_vertex,cube_rotation.z);
            transform_vertex.z -= camera.z;
            vec2_t projected_point = project2D(FOV,transform_vertex);
            projected_point.x += position.x;
            projected_point.y += position.y;
            projected_triangle.points[j] = projected_point;
        }
        uint8_t code = dynArray_push_back(triangles_to_render,&projected_triangle);
        if(code != 0)
        {
            exit(EXIT_FAILURE);
        }
    }
}

void draw_mesh(void)
{
    size_t triangle_length = dynArray_get_length(triangles_to_render);
    for (int i = 0; i < triangle_length; i++)
    {
        triangle_t *triangle = dynArray_get_item(triangles_to_render, i); //triangles_to_render[i];
        draw_rect(triangle->points[0].x, triangle->points[0].y, 3, 3, 0xFFFF00FF);
        draw_rect(triangle->points[1].x, triangle->points[1].y, 3, 3, 0xFFFF00FF);
        draw_rect(triangle->points[2].x, triangle->points[2].y, 3, 3, 0xFFFF00FF);
        draw_triangle(triangle->points[0].x,
                      triangle->points[0].y,
                      triangle->points[1].x,
                      triangle->points[1].y,
                      triangle->points[2].x,
                      triangle->points[2].y,
                      0xFFFF0000);
    }
    dynArray_clear(triangles_to_render);
}
