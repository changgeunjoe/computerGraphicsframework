#version 330

layout (location = 0) in vec3 a_Position; 
uniform mat4 u_WorldMatrix;
uniform mat4 u_ViewMatrix;


///////////////////////////
out vec3 v_Color;


void main()
{
	v_Color=a_Position*5;
	gl_Position = u_WorldMatrix * vec4(a_Position, 1.0f)*u_ViewMatrix;
}
