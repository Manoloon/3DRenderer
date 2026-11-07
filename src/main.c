#include <SDL2/sdl.h>
#include "display.h"
#include "exercises.h"
#include "globals.h"
#include "vector.h"

#define N_POINTS 9*9*9
vec3_t cube[N_POINTS];
vec2_t projected_points[N_POINTS];
float fov_factor = 1240.0;
int fov_acc = 2;
float rot_x = 0.0;
float rot_y = 0.0;
float rot_z = 0.0;
vec3_t camera ={0.0,0.0,-5.0};
vec3_t obj_rotation = {0,0,0};
vec2_t project2D(vec3_t points)
{
    vec2_t projected ={(points.x * fov_factor)/points.z,(points.y * fov_factor)/points.z};
    return projected;
}

// remember 0xFFEE1100 -> 0xAA-RR-GG-BB
bool begin_play()
{
    color_buffer = (uint32_t*)malloc(sizeof(uint32_t) * window_width * window_height);
    if(color_buffer == NULL)
    {
        fprintf(stderr,"Failed to allocate memory for the color buffer\n");
        return false;
    }
    color_buffer_texture = SDL_CreateTexture(renderer,
                                SDL_PIXELFORMAT_ARGB8888,
                                SDL_TEXTUREACCESS_STREAMING,
                                window_width,window_height);
    if(color_buffer_texture == NULL)
    {
        fprintf(stderr,"FAILED to construct the color buffer texture\n");
        return false;
    }

    // cube
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
    return true;
}

void process_input(void)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            is_app_running = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                is_app_running = false;
                break;
            case SDLK_w:
                if(fov_factor < 3000)
                    fov_factor +=fov_acc;
                break;
            case SDLK_s:
                if(fov_factor > 0)
                    fov_factor -=fov_acc;
                break;
            case SDLK_UP:
                if(rot_y < 0.1)
                {
                    rot_y +=0.001;
                    break;
                }
            case SDLK_DOWN:
                if(rot_y > -0.1)
                {
                    rot_y -=0.001;
                    break;
                }
            case SDLK_RIGHT:
                if(rot_x < 0.1)
                {
                    rot_x +=0.001;
                    break;
                }
            case SDLK_LEFT:
                if(rot_x > -0.1)
                {
                    rot_x -=0.001;
                    break;
                }
            case SDLK_SPACE:
                if(rot_z == 0.0)
                {
                    rot_z =0.005;
                    break;
                }
                else
                {
                    rot_z = 0.0;
                }
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
}


void draw(void)
{
    draw_grid(0xFF646464,8);
    for(int i= 0; i < N_POINTS;i++)
    {
        vec2_t projected = projected_points[i];
        draw_rect((projected.x+window_width) * 0.5,
                (projected.y+window_height) * 0.5,
                    4,4,0xFF00FF00);
    }
    renderColorBuffer();

    clearColorBuffer(0xFF000000);
    SDL_RenderPresent(renderer);
}


void update(void)
{
    obj_rotation.x += rot_x;
    obj_rotation.y += rot_y;
    obj_rotation.z +=rot_z;
    // transformation of vectors
    // projection of vectors
    for(int i = 0; i < N_POINTS;i++)
    {
        vec3_t point = cube[i];
        vec3_t transform_point = vec3_rotate_x(point,obj_rotation.x);
        transform_point = vec3_rotate_y(transform_point,obj_rotation.y);
        transform_point = vec3_rotate_z(transform_point,obj_rotation.z);
        transform_point.z -= camera.z;
        projected_points[i] = project2D(transform_point);
    }
}

int main(int argc, char* args[])
{
    is_app_running = init_window();
    if(!begin_play())
    {
        is_app_running = false;
    }

    while(is_app_running)
    {
        process_input();
        update();
        draw();
    }
    destroy_window();
    return 0;
}