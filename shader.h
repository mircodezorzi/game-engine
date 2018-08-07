#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

#define NUM_SHADERS 2

typedef struct {
    GLuint shader_program;
    GLuint shaders[NUM_SHADERS];
} s_shader;

s_shader* s_new(const char[]);
void      s_destroy(s_shader *);
void      s_bind(s_shader *);

GLuint s_create(const char[], GLenum);
void   s_check_for_errors(GLuint, GLuint, int, const char[]);
char*  s_load(char[]);

#endif
