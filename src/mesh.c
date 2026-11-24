#include "mesh.h"
#include "display.h"
#include "parser.h"
#include "exercises.h"
#include "triangle.h"
#include "globals.h"

FILE* obj_file = NULL;

mesh_t mesh =
    {
        .vertices = NULL,
        .faces = NULL,
        .rotation = {0.0,0.0,0.0}
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

void create_mesh(void)
{
    triangles_to_render = dynArray_create(sizeof(triangle_t));
    // loading obj
    const char* filename = "assets/cube.obj";
    obj_file = fopen(filename,"r");
    if(obj_file == NULL)
    {
        fprintf(stderr,"Create Mesh: failed to load obj file\n");
        exit(EXIT_FAILURE);
    }
    bool bsuccess = start_parsing(obj_file,&mesh);
    if(!bsuccess)
    {
        fprintf(stderr,"Create Mesh : failed parsing\n");
        exit(EXIT_FAILURE);
    }
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
