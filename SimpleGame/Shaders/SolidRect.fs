#version 330

layout(location=0) out vec4 FragColor; 
uniform vec4 u_Color;

void main()
{
	FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
