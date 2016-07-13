#version 330

layout(location = 0) in vec3 in_position;		
layout(location = 1) in vec3 in_normal;		

uniform vec3 lightPosition;
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec3 color;
void main()
{	
	color = in_normal;

	gl_Position = Projection * View * Model * vec4(in_position, 1); 
}
