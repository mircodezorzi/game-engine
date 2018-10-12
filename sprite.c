#include "sprite.h"

#include <stdlib.h>

sprite_t *sprite_new(vec2 position, vec2 size, float scale, const char *texture_filepath){
    sprite_t *s = malloc(sizeof(sprite_t));

    s->verticies[0] = vertex_new(
            position.x * scale,
            position.y * scale,
            0.0, 0.0, 0.0);
    s->verticies[1] = vertex_new(
            position.x + size.x * scale,
            position.y * scale,
            0.0, 1.0, 0.0);
    s->verticies[2] = vertex_new(
            position.x * scale,
            position.y + size.y * scale,
            0.0, 0.0, 1.0);
    s->verticies[3] = vertex_new(
            position.x + size.x * scale,
            position.y + size.y * scale,
            0.0, 1.0, 1.0);

    s->indicies[0] = 0;
    s->indicies[1] = 1;
    s->indicies[2] = 2;
    s->indicies[3] = 1;
    s->indicies[4] = 2;
    s->indicies[5] = 3;

    s->texture = texture_new(texture_filepath);
    s->mesh = mesh_new(s->verticies, 4, s->indicies, 6);
    s->position = position;
    s->size = size;
    s->scale = scale;

    return s;
}

void sprite_destroy(sprite_t *s){
    mesh_destroy(s->mesh);
    texture_destroy(s->texture);
    free(s);
    s = NULL;
}

void sprite_draw(sprite_t *s){
    mesh_draw(s->mesh);
}
