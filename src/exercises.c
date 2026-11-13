#include "exercises.h"
#include "globals.h"
#include "display.h"
vec3_t cube[N_POINTS];
vec2_t projected_points[N_POINTS];
vec3_t obj_rotation = {0,0,0};

void create_vertex_cube(void) 
{
    int point_count =0;
    for(float x = -1.0; x <= 1; x +=0.25)
    {
        for(float y = -1.0; y <= 1; y +=0.25)
        {
            for(float z = -1.0; z <= 1; z +=0.25)
            {
                vec3_t new_point={x,y,z};
                cube[point_count++] = new_point;
            }
        }
    }
}

void draw_vertex_cube(vec2_t position) 
{
    for(int i= 0; i < N_POINTS;i++)
    {
        vec2_t projected = projected_points[i];
        draw_rect(projected.x+position.x,projected.y+position.y,
                    4,4,0xFF00FF00);
    }
}

void update_vertex_cube(float FOV, vec3_t rot_speed,vec3_t camera) 
{
    obj_rotation.x += rot_speed.x;
    obj_rotation.y += rot_speed.y;
    obj_rotation.z += rot_speed.z;
    // transformation of vectors
    // projection of vectors
    for(int i = 0; i < N_POINTS;i++)
    {
        vec3_t point = cube[i];
        vec3_t transform_point = vec3_rotate_x(point,obj_rotation.x);
        transform_point = vec3_rotate_y(transform_point,obj_rotation.y);
        transform_point = vec3_rotate_z(transform_point,obj_rotation.z);
        transform_point.z -= camera.z;
        projected_points[i] = project2D(FOV,transform_point);
    }
}
