#version 330 core

#define PI 3.1415926535897932

in vec3 Position;

out vec4 outColor;

uniform float checkerFreq;


vec3 checker(vec3 p,float freq){
	vec3 q = freq*p*2.0*PI;
	if(sin(q.x)*sin(q.y)*sin(q.z) >= 0) return vec3(0.7);
	else return vec3(0.3);
}

void main()
{
	//outColor = vec4(Position,1.0);
	outColor = vec4(checker(Position,checkerFreq),1.0);
}