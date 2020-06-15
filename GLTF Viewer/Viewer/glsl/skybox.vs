#version 330 core
layout (location = 0) in vec3 i_Pos;
out vec3 v_TexCoord;

uniform mat4 u_ProjViewModel;

void main(){
    gl_Position = u_ProjViewModel * vec4(i_Pos, 1.0);
    v_TexCoord = i_Pos;
}