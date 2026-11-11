#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT

#define NK_IMPLEMENTATION
#define NK_SDL_RENDERER_IMPLEMENTATION
#include "nuklear.h"
#include "nuklear_sdl_renderer.h"

#include "gui.h"
#include <string.h>

static struct nk_context* ctx = NULL;
static bool initialized = false;

bool gui_init(SDL_Window* window,SDL_Renderer* renderer)
{
    if(!window || !renderer)
    {
        fprintf(stderr,"Gui: Window or renderer failed to load");
        return false;
    }
        
    ctx = nk_sdl_init(window,renderer);
    if(!ctx)
    {
        fprintf(stderr,"Gui: Context failed");
        return false;
    }
    struct nk_font_atlas* atlas;
    struct nk_font_config config = nk_font_config(0);
    struct nk_font* font;

    nk_sdl_font_stash_begin(&atlas);
    font = nk_font_atlas_add_default(atlas,13 * 10.0f,&config);
    nk_sdl_font_stash_end();
    nk_style_set_font(ctx, &font->handle);
    initialized = true;
    return initialized;
}

void gui_process_event(SDL_Event *event)
{
    if(!initialized || !event)
        return;
    nk_sdl_handle_event(event);
}

void gui_begin(void)
{
    if(!initialized)
        return;
    nk_input_begin(ctx);
}

void gui_build(void)
{
    if(!initialized)
        return;
    
    if(nk_begin(ctx,"3D Renderer",
                nk_rect(50,50,350,250),
                NK_WINDOW_BORDER | 
                NK_WINDOW_MOVABLE |
                NK_WINDOW_TITLE |
                NK_WINDOW_SCALABLE))
        {
            nk_layout_row_dynamic(ctx,30,1);
            nk_label(ctx,"GUI NUKLEAR",NK_TEXT_LEFT);
            if(nk_button_label(ctx,"yo el boton"))
            {
                SDL_Log("button pressed");
            }
            static int enabled = 0;
            nk_checkbox_label(ctx,"enable feature",&enabled);
            static float value = 0.5f;
            nk_layout_row_dynamic(ctx,25,1);
            nk_slide_float(ctx,0.0f,value,1.0f,0.01f);
        }
        nk_end(ctx);
}

void gui_end(void)
{
    if(!initialized)
        return;
    nk_sdl_render(NK_ANTI_ALIASING_ON);
}

void gui_shutdown(void)
{
    ctx = NULL;
    initialized = false;
}

struct nk_context *gui_get_context(void)
{
    return ctx;
}
