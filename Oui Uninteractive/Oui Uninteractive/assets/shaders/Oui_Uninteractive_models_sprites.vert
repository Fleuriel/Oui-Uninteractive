#version 450 core


layout (location=0) in vec2 aVertexPosition;
layout (location=1) in vec3 aVertexColor;
layout (location=2) in vec2 aVertexTexture;

layout (location=0) out vec3 vColor;
layout (location=1) out vec2 vTex;

uniform int col_To_Draw;
uniform int rows;
uniform int cols;
uniform int row_To_Draw;

uniform mat3 uModel_to_NDC;


out vec3 FragPos;


out vec2 TexCoord;  // Pass texture coordinates to the fragment shader

void main(void){

	mat3 normalMatrix = transpose(inverse(mat3(uModel_to_NDC)));

	vec4 worldPosition = vec4(vec2(uModel_to_NDC * vec3(aVertexPosition, 1.0f)), 0.0, 1.0);


	//set the position
	gl_Position =  worldPosition;
	//set the color
	vColor = aVertexColor;

	float width = aVertexTexture.x / cols;
	float height = aVertexTexture.y / rows;

	vTex = vec2(width , height) + vec2(float(col_To_Draw)/float(cols),float(row_To_Draw)/float(rows));

	TexCoord = aVertexTexture;




        // Pass the world-space position to the fragment shader
        FragPos = vec3(worldPosition);
}