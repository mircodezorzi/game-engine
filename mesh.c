#include <stdlib.h>
#include <stdio.h>

#include "mesh.h"

vec2 vec2_new(float x, float y){
    vec2 v;
    v.x = x;
    v.y = y;
    return v;
}

vec3 vec3_new(float x, float y, float z){
    vec3 v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

vertex *vertex_new(float x, float y, float z, float m, float n){
    vertex *v = malloc(sizeof(vertex));
    v->pos = vec3_new(x, y, z);
    v->tex = vec2_new(m, n);
    return v;
}

m_mesh *m_new(vertex *verticies[], unsigned int vertex_count, unsigned int *indicies, unsigned int indicies_count){
    m_mesh *m = malloc(sizeof(m_mesh));
    m->draw_count = indicies_count;

    glGenVertexArrays(1, &m->VAO);
    glBindVertexArray(m->VAO);

    vec3 *pos = malloc(vertex_count * sizeof(vec3));
    vec2 *tex = malloc(vertex_count * sizeof(vec2));

    for(unsigned int i = 0; i < vertex_count; i++){
        pos[i] = verticies[i]->pos;
        tex[i] = verticies[i]->tex;
    }

    glGenBuffers(NUM_BUFFERS, m->VAB);
    glBindBuffer(GL_ARRAY_BUFFER, m->VAB[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(pos[0]), pos, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


    glGenBuffers(NUM_BUFFERS, m->VAB);
    glBindBuffer(GL_ARRAY_BUFFER, m->VAB[TEXTCORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(tex[0]), tex, GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->VAB[INDEX_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies_count * sizeof(indicies[0]), indicies, GL_STATIC_DRAW);

    glBindVertexArray(0);

    return m;
}

void m_destroy(m_mesh *m){
    glDeleteVertexArrays(1, m->VAO);
    free(m);
}

void m_draw(m_mesh *m){
    glBindVertexArray(m->VAO);
    glDrawElements(GL_TRIANGLES, m->draw_count, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
