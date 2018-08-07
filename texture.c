#include "stb_image.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "texture.h"

t_texture *t_new(const char filepath[]){
    t_texture *t = malloc(sizeof(t_texture));
    unsigned int width, height;
    unsigned char* image = stbi_load(filepath, &width, &height, NULL, 4);

    if(!image)
        printf("texture loading failed for texture: %s:", filepath);

    glGenTextures(1, &t->texture);
    glBindTexture(GL_TEXTURE_2D, t->texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    stbi_image_free(image);
}

void t_destroy(t_texture *t){
    glDeleteTextures(1, &t->texture);
}

void t_bind(t_texture *t, unsigned int unit){
    assert(unit >= 0 && unit <= 31);
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, t->texture);
}
