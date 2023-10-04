#version 330

layout (location = 0) in vec3 a_Position; 
uniform mat4 u_WorldMatrix;

void main()
{
	gl_Position = u_WorldMatrix * vec4(a_Position, 1.0f);
}
