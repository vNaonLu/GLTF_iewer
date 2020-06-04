#version 330 core
in vec3 v_tex_coords;
out vec4 color;

uniform samplerCube tex_skybox;

void main(){
    color = texture(tex_skybox, v_tex_coords);
}