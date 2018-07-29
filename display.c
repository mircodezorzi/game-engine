#include "display.h"

#include<SDL2/SDL.h>
#include<GL/glew.h>
#include<stdio.h>

d_display *d_new(int width, int height, const char title[]){
    d_display *d = malloc(sizeof(d_display));

    SDL_Init(SDL_INIT_VIDEO);

    d->window = SDL_CreateWindow(
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

    if(!d->window && DEBUGGING)
        printf("error initializing window: %s\n", SDL_GetError());

    d->context = SDL_GL_CreateContext(d->window);

    GLenum status = glewInit();
    if(status != GLEW_OK && DEBUGGING)
        printf("error initializing glew");

    d->close_request = 0;

    return d;
}

void d_free(d_display *d){
    SDL_GL_DeleteContext(d->context);
    SDL_DestroyWindow(d->window);
    SDL_Quit();
}

void d_update(d_display *d){
    SDL_GL_SwapWindow(d->window);

    SDL_Event event;
    while(SDL_PollEvent(&event))
        switch(event.type){
            case SDL_QUIT:
                d->close_request = 1;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.scancode){
                    case SDLK_ESCAPE:
                        d->close_request = 1;
                        break;
                }
        }
}

void d_clear(float r, float g, float b, float a){
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}
