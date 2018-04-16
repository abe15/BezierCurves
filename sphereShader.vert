
#version 330 core
layout (location = 0) in vec3 position;
//layout (location = 1) in vec3 normal;

out vec3 Normal;
out vec3 Position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
    //Normal = mat3(transpose(inverse(model))) * normal;
	//need sphere center
	//vec3 v(model[4][1],model[4][2],model[4][3],1.0f);
	vec3 v = vec3(model[3][0],model[3][1],model[3][2]);
	Normal = mat3(transpose(inverse(model))) * (position - v);
    Position = vec3(model *view* vec4(position, 1.0f));
}  