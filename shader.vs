#version 330 core

out vec4 FragColor;

in vec3 shader_color;
in vec2 texture_coords;

uniform sampler2D texture_sample;

void main(){
    FragColor = texture(texture_sample, texture_coords);
}
