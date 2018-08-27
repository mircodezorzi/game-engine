#include "window.h"

#include<SDL2/SDL.h>
#include<GL/glew.h>
#include<stdio.h>

window_t *window_new(
        unsigned int width,
        unsigned int height,
        const char *title,
        void (*event_callback)(SDL_Event)){

    window_t *w = malloc(sizeof(window_t));

    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);

    w->window = SDL_CreateWindow(
            title,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width,
            height,
            SDL_WINDOW_OPENGL);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    if(!w->window && DEBUGGING)
        printf("error initializing window: %s\n", SDL_GetError());

    w->context = SDL_GL_CreateContext(w->window);

    GLenum status = glewInit();
    if(status != GLEW_OK && DEBUGGING)
        printf("error initializing glew");

    w->close_request = 0;
    w->event_callback = event_callback;

    return w;
}

void window_destroy(window_t *w){
    SDL_GL_DeleteContext(w->context);
    SDL_DestroyWindow(w->window);
    SDL_Quit();
    free(w);
}

void window_update(window_t *w){
    SDL_GL_SwapWindow(w->window);

    SDL_Event event;
    while(SDL_PollEvent(&event))
        switch(event.type){
            case SDL_QUIT:
                w->close_request = 1;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.scancode){
                    case SDLK_ESCAPE:
                        w->close_request = 1;
                        break;
                }
        }

    (*w->event_callback)(event);

}

void window_fill(float r, float g, float b, float a){
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}
