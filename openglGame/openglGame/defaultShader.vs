#version 330 core


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    TexCoords = aTexCoords;    
     gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}