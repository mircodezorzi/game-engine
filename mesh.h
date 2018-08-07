#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>

typedef struct{
    float x, y, z;
} vec3;

vec3 vec3_new(float, float, float);

typedef struct{
    float x, y;
} vec2;

vec2 vec2_new(float, float);

typedef struct{
    vec3 pos;
    vec2 tex;
} vertex;

vertex *vertex_new(float, float, float, float, float);

typedef struct{
    enum{
        POSITION_VB,
        TEXTCORD_VB,
        NUM_BUFFERS
    };
    GLuint VAO;
    GLuint VAB[NUM_BUFFERS];
    unsigned int draw_count;
} m_mesh;

m_mesh *m_new(vertex *[], unsigned int);
void    m_destroy(m_mesh *);

void m_draw(m_mesh *);

#endif
