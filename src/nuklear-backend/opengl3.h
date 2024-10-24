#ifndef NK_SDL_GL3_H_
#define NK_SDL_GL3_H_

#include <nuklear-backend/nuklear_imp.h>
#include <SDL2/SDL.h>
#include <glad/glad.h>

NK_API struct nk_context* nk_sdl_init(SDL_Window* win);
NK_API void                 nk_sdl_font_stash_begin(struct nk_font_atlas** atlas);
NK_API void                 nk_sdl_font_stash_end(void);
NK_API int                  nk_sdl_handle_event(SDL_Event* evt);
NK_API void                 nk_sdl_render(enum nk_anti_aliasing, int max_vertex_buffer, int max_element_buffer);
NK_API void                 nk_sdl_shutdown(void);
NK_API void                 nk_sdl_device_destroy(void);
NK_API void                 nk_sdl_device_create(void);
NK_API void                 nk_sdl_handle_grab(void);
#endif