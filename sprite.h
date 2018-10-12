#ifndef SPRITE_H
#define SPRITE_H

//#include "mathlib.h"
#include "texture.h"
#include "mesh.h"

// TODO temporary
typedef m_mesh mesh_t;
typedef t_texture texture_t;
#define texture_new t_new
#define mesh_new m_new
#define texture_destroy t_destroy
#define mesh_destroy m_destroy
#define mesh_draw m_draw
#define texture_bind t_bind

typedef struct{
    vec2 position, size;
    float scale;
    vertex *verticies[4];
    unsigned int indicies[6];
    texture_t *texture;
    mesh_t *mesh;
} sprite_t;

sprite_t *sprite_new(vec2, vec2, float, const char*);
void sprite_destroy(sprite_t *);
void sprite_draw(sprite_t *s);

#endif
