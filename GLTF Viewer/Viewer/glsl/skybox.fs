#version 330 core
in vec3 v_TexCoord;
out vec4 outColor;

uniform samplerCube u_TexSkybox;

void main(){
    outColor = texture(u_TexSkybox, v_TexCoord);
}