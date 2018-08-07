#ifndef DISPLAY_H
#define DISPLAY_H

#include<SDL2/SDL.h>

#define DEBUGGING 1

typedef struct{
    SDL_Window *window;
    SDL_GLContext *context;
    int close_request;
} d_display;

d_display* d_new(int, int, const char[]);
void       d_destroy(d_display *);
void       d_update(d_display *);
void       d_clear(float, float, float, float);

#endif
