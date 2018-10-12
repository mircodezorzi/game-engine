#include "window.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"

#include "sprite.h"

#include <SDL2/SDL.h>
void input(SDL_Event event){
    while(SDL_PollEvent(&event))
        switch(event.type){
            default:
                break;
        }
}

int main(void){

    window_t *w = window_new(800, 600, "engine", input);
    s_shader  *s = s_new("shader");

    glViewport(10,20,500,500);

    sprite_t *player = sprite_new(vec2_new(0, 0), vec2_new(1, 1), 1, "bricks.jpg");

    while(!w->close_request){
          window_fill(0.0f, 0.15f, 0.3f, 1.0f);

          s_bind(s);
          sprite_draw(player);
          window_update(w);
    }

    sprite_destroy(player);
    s_destroy(s);
    window_destroy(w);

}
