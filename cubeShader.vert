#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
//layout (location = 2) in vec3 texcoords;

out vec3 Normal;
out vec3 Position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
   gl_Position = projection * model* view  * vec4(position.x,position.y,position.z , 1.0f);
    Normal = mat3(transpose(inverse(model))) * normal;
    Position = vec3(vec4(position, 1.0f));
}  