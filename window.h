#ifndef WINDOW_H
#define WINDOW_H

#include<SDL2/SDL.h>

#define DEBUGGING 1

typedef struct{
    SDL_Window *window;
    SDL_GLContext *context;
    int close_request;
    void (*event_callback)(SDL_Event);
} window_t;

window_t* window_new(
        unsigned int,
        unsigned int,
        const char *,
        void (*)(SDL_Event));
void window_destroy(window_t *);
void window_update(window_t *);
void window_fill(float, float, float, float);

#endif
