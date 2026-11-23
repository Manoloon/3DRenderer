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

//vec3_t cube_rotation = {0.0,0.0,0.0};
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
dynarray_t* triangles_to_render = NULL;
void load_cube_data(void)
{
    mesh.vertices = dynArray_create(sizeof(vec3_t));
    if(mesh.vertices == NULL)
    {
        fprintf(stderr,"loadCube : Mesh.vertices is NULL");
        exit(EXIT_FAILURE);
    }
    mesh.faces = dynArray_create(sizeof(face_t));
    if(mesh.faces == NULL)
    {
        fprintf(stderr,"loadCube : Mesh.faces is NULL");
        exit(EXIT_FAILURE);
    }
    
    for(int i = 0; i < N_CUBE_VERTICES; i++)
    {
        vec3_t cube_vertex = cube_vertices[i];
        dynArray_push_back(mesh.vertices,&cube_vertex);
    }
    for(int i = 0; i < N_CUBE_FACES;i++)
    {
        face_t cube_face = cube_faces[i];
        dynArray_push_back(mesh.faces,&cube_face);
    }
}
void create_mesh(void)
{
    triangles_to_render = dynArray_create(sizeof(triangle_t));
    load_cube_data();
}
void update_mesh(vec2_t position,float FOV, vec3_t rot_speed,vec3_t camera)
{
    mesh.rotation.x += rot_speed.x;
    mesh.rotation.y += rot_speed.y;
    mesh.rotation.z += rot_speed.z;
    int faces_num = (int) dynArray_get_length(mesh.faces);
    for(int i = 0; i < faces_num;i++)
    {
        face_t* current_face = dynArray_get_item(mesh.faces,i);
        vec3_t* face_vertices[3];

        face_vertices[0] = dynArray_get_item(mesh.vertices,current_face->a -1); 
        face_vertices[1] = dynArray_get_item(mesh.vertices,current_face->b -1);
        face_vertices[2] = dynArray_get_item(mesh.vertices,current_face->c -1); 

        triangle_t projected_triangle;
        
        for(int j = 0; j < 3;j++)
        {
            vec3_t transform_vertex = *face_vertices[j];
            transform_vertex = vec3_rotate_x(transform_vertex,mesh.rotation.x);
            transform_vertex = vec3_rotate_y(transform_vertex,mesh.rotation.y);
            transform_vertex = vec3_rotate_z(transform_vertex,mesh.rotation.z);
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
    int triangle_length = (int)dynArray_get_length(triangles_to_render);
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
