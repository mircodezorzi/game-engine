#include <stdlib.h>
#include <stdio.h>

#include "shader.h"

s_shader* s_new(const char filepath[]){
    s_shader *s = malloc(sizeof(s_shader));

    s->shader_program = glCreateProgram();
    s->shaders[0] = s_create(s_load("shader.vs"), GL_VERTEX_SHADER);
    s->shaders[1] = s_create(s_load("shader.fs"), GL_FRAGMENT_SHADER);

    for(unsigned int i = 0; i < NUM_SHADERS; i++)
        glAttachShader(s->shader_program, s->shaders[i]);

    glBindAttribLocation(s->shader_program, 0, "position");
    glBindAttribLocation(s->shader_program, 1, "texture_positions");

    glLinkProgram(s->shader_program);
    s_check_for_errors(s->shader_program, GL_LINK_STATUS, 1, "error: shader program failed to link");

    glValidateProgram(s->shader_program);
    s_check_for_errors(s->shader_program, GL_LINK_STATUS, 1, "error: shader program is invalid");

    return s;
}

void s_destroy(s_shader *s){
    char *buffer = NULL;
    for(unsigned int i = 0; i < NUM_SHADERS; i++){
        glDetachShader(s->shader_program, s->shaders[i]);
        glDeleteShader(s->shaders[i]);
    }
    glDeleteProgram(s->shader_program);
    free(s);
}

void s_bind(s_shader *s){
    glUseProgram(s->shader_program);
}

GLuint s_create(const char text[], GLenum shader_type){
    GLuint shader = glCreateShader(shader_type);

    if(!shader)
        printf("error: shader creation failed\n");

    const GLchar *p[1] = { text };
    GLint p_length[1] = { strlen(text) };

    glShaderSource(shader, 1, p, p_length);
    glCompileShader(shader);

    s_check_for_errors(shader, GL_COMPILE_STATUS, 0, "error: shader compilation failed");

    return shader;
}

char* s_load(char filepath[]){
    FILE  *file = fopen(filepath, "r");
    char *buffer;
    long length;

    if(!file)
        printf("error opening file: %s\n", filepath);

    fseek(file, 0, SEEK_END);
    length = ftell(file);
    rewind(file);

    buffer = malloc((length + 1) * sizeof(*buffer));
    fread(buffer, length, 1, file);
    buffer[length] = '\0';

    fclose(file);
    return buffer;
}

void s_check_for_errors(GLuint shader, GLuint flag, int is_program, const char error_message[]){
    GLint success = 0;
    GLchar error[1024] = {0};

    if(is_program)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if(success == GL_FALSE){
        if(is_program)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);
        printf("%s: '%s'", error_message, error);
    }
}
