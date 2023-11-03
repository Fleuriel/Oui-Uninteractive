#version 450 core


layout (location=0) in vec2 aVertexPosition;
layout (location=1) in vec3 aVertexColor;
layout (location=2) in vec2 aVertexTexture;

layout (location=0) out vec3 vColor;
layout (location=1) out vec2 vTex;

uniform int fr;
uniform int r;
uniform int c;

uniform mat3 uModel_to_NDC;

void main(void){

	//set the position
	gl_Position = vec4(vec2(uModel_to_NDC * vec3(aVertexPosition, 1.f)), 0.0, 1.0);
	//set the color
	vColor = aVertexColor;

	float width = aVertexTexture.x / c;
	float height = float(aVertexTexture.y) / float(r);



	vTex = vec2(width , height) + vec2(float(fr)/float(r*c),0);

	vColor = vec3(fr,r,c);


	// Set the texture to the 'bytes'
	//vTex = aVertexTexture;

}