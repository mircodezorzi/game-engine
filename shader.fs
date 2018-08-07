#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color0;
layout (location = 2) in vec2 texture_coordinates0;

out vec3 shader_color;
out vec2 texture_coordinates;

void main(){
    gl_Position = vec4(position0, 1.0);
    shader_color = color0;
    texture_coordinates = texture_coordinates0;
}
