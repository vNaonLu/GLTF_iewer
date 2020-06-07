#version 330 core
layout (location = 0) in vec3 i_pos;
out vec3 v_tex_coords;

uniform mat4 model_proj_view;

void main(){
    gl_Position = model_proj_view * vec4(i_pos, 1.0);
    v_tex_coords = i_pos;
}