#include "mesh.h"
#include "display.h"
#include "parser.h"
#include "exercises.h"
#include "triangle.h"
#include "globals.h"

mesh_t mesh =
    {
        .vertices = NULL,
        .faces = NULL,
        .rotation = {0.0,0.0,0.0}
    };
dynarray_t* triangles_to_render = NULL;

bool create_mesh(void)
{
    triangles_to_render = dynArray_create(sizeof(triangle_t));
    if(triangles_to_render == NULL)
    {
        fprintf(stderr,"Create Mesh: failed to load obj file\n");
        return false;
    }
    // loading obj
    const char* filename = "assets/cube.obj";
    bool bsuccess = start_parsing(filename,&mesh);
    return bsuccess;
}
void update_mesh(vec2_t position,float FOV, vec3_t rot_speed,vec3_t camera)
{
    int faces_num = (int) dynArray_get_length(mesh.faces);
    mesh.rotation.x += rot_speed.x;
    mesh.rotation.y += rot_speed.y;
    mesh.rotation.z += rot_speed.z;

    for(int i = 0; i < faces_num;i++)
    {
        face_t* current_face = dynArray_get_item(mesh.faces,i);
        vec3_t* face_vertices[3];
        face_vertices[0] =dynArray_get_item(mesh.vertices,current_face->a-1); 
        face_vertices[1] =dynArray_get_item(mesh.vertices,current_face->b-1);
        face_vertices[2] =dynArray_get_item(mesh.vertices,current_face->c-1); 

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
        uint8_t bSuccess = dynArray_push_back(triangles_to_render,&projected_triangle);
        if(bSuccess != 0)
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
