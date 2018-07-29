#include<SDL2/SDL.h>
#include<GL/glew.h>

#include "display.h"

int main(void){
    d_display *d = d_new(640, 480, "Game");
    while(!d->close_request){
          d_clear(0.0f, 0.15f, 0.3f, 1.0f);
          d_update(d);
    }
    d_free(d);
}
