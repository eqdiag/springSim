#version 330 core

in vec3 Position;
in vec3 Normal;

out vec4 outColor;

const vec3 light = vec3(0,2000,0);

uniform vec3 eye;

void main()
{
	float diff = max(dot(Normal,normalize(eye - Position)),0.0)*.5;
	//vec3 diffCol = diff*vec3(1.0);
	//Add ambient term
	vec3 col = vec3(diff) + vec3(0.5);
	outColor = vec4(col,1.0);
}