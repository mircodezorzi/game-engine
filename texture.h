#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

typedef struct{
    GLuint texture;
} t_texture;

t_texture *t_new(const char[]);
void       t_destroy(t_texture *);

void t_bind(t_texture *t, unsigned int unit);

#endif
