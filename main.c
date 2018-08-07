#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"

#include <GL/glew.h>

int main(void){

    vertex *verticies[3] = {
        vertex_new(-0.5, -0.5, 0.0, 0.0, 0.0),
        vertex_new( 0.0,  0.5, 0.0, 0.5, 1.0),
        vertex_new( 0.5, -0.5, 0.0, 1.0, 0.0)
    };

    d_display *d = d_new(640, 480, "Game");
    s_shader  *s = s_new("shader");
    m_mesh    *m = m_new(verticies, 3);
    t_texture *t = t_new("bricks.jpg");

    while(!d->close_request){
          d_clear(0.0f, 0.15f, 0.3f, 1.0f);




    float timeValue = 1;
    float greenValue = sin(timeValue) / 2.0f + 0.5f;
    int vertexColorLocation = glGetUniformLocation(s->shader_program, "diffuse");
    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);


          s_bind(s);
          t_bind(t, 0);
          m_draw(m);
          d_update(d);
    }

    d_destroy(d);
    s_destroy(s);
    m_destroy(m);
    t_destroy(t);

}
