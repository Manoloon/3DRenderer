#include <SDL2/sdl.h>
#include "display.h"
#include "exercises.h"
#include "mesh.h"
#include "globals.h"
#include "vector.h"
#include "gui.h"

float fov_factor = 1240.0;
int fov_acc = 2;
vec3_t rotation_speed = {0.0,0.0,0.0};
vec2_t world_position ={100,240};
static int mouse_x;
static int mouse_y;
static bool left_click;
uint32_t prev_frame_time = 0;

vec3_t camera ={0.0,0.0,-15.0};

// remember 0xFFEE1100 -> 0xAA-RR-GG-BB
bool begin_play()
{
    color_buffer = (uint32_t*)malloc(sizeof(uint32_t) * window_width * window_height);
    if(color_buffer == NULL)
    {;
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
    create_vertex_cube();
    return true;
}

int process_input(void)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        // Gui
        gui_process_event(&event);

        switch (event.type)
        {
        case SDL_QUIT:
            is_app_running = false;
            return 0;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    is_app_running = false;
                    return 0;
                case SDLK_w:
                    if(world_position.y < window_height)
                        world_position.y +=1;
                    return 0;
                case SDLK_s:
                    //if(fov_factor > 0)
                      //  fov_factor -=fov_acc;
                    if(world_position.y > 0)
                        world_position.y -=1;
                    return 0;
                case SDLK_a:
                    if(world_position.x > 0)
                        world_position.x-=1;
                    return 0;
                case SDLK_d:
                    if(world_position.x < window_width)
                        world_position.x +=1;
                    return 0;
                case SDLK_UP:
                    if(rotation_speed.y < 0.1)
                        rotation_speed.y +=0.001;
                    return 0;
                case SDLK_DOWN:
                    if(rotation_speed.y > -0.1)
                        rotation_speed.y -=0.001;
                    return 0;
                case SDLK_RIGHT:
                    if(rotation_speed.x < 0.1)
                        rotation_speed.x +=0.001;
                    return 0;
                case SDLK_LEFT:
                    if(rotation_speed.x > -0.1)
                        rotation_speed.x -=0.001;
                    return 0;
                case SDLK_SPACE:
                    rotation_speed.z = rotation_speed.z == 0.0 ? 0.005 : 0.0; 
                    return 0;
                case SDL_MOUSEMOTION:
                    mouse_x = event.motion.x;
                    mouse_y = event.motion.y;
                    return 0;
                case SDL_MOUSEBUTTONDOWN:
                    left_click = true;
                    if(fov_factor < 3000)
                        fov_factor +=fov_acc;
                    return 0;
                case SDL_MOUSEBUTTONUP:
                    left_click = false;
                    return 0;
                default:
                    return 0;
            }
        }
    }
}

void draw(void)
{
    draw_grid(0xFF646464,8);
    vec2_t newPos = {(window_width/2)+200,window_height/2};
    draw_vertex_cube(newPos);
    draw_mesh();
    renderColorBuffer();

    // Gui
    gui_end();

    clearColorBuffer(0xFF000000);
    SDL_RenderPresent(renderer);
}


void update(void)
{  
    prev_frame_time = SDL_GetTicks();
    update_vertex_cube(fov_factor,rotation_speed,camera);
    update_mesh(0.016,world_position,fov_factor,rotation_speed,camera);
}

int main(int argc, char* args[])
{
    is_app_running = init_window();
    if(!begin_play())
    {
        is_app_running = false;
    }
    gui_init(window,renderer);
    while(is_app_running)
    {
        int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() + prev_frame_time);
        if(time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME)
        {
            SDL_Delay(time_to_wait);
        }
        // GUi
        gui_begin();

        process_input();
        gui_build();
        update();
        draw();
    }
    gui_shutdown();
    destroy_window();
    return 0;
}