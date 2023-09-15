/*!
@file		my-tutorial-3.vert
@author		pghali@digipen.edu
@co-author	zijun.tok@gmail.com
@date		05/25/2023

vertex shader file
*//*__________________________________________________________________________*/

#version 450 core
//getting vertex position from vaoid 0
layout (location=0) in vec2 aVertexPosition;

uniform mat3 uModel_to_NDC;

void main() {
gl_Position = vec4(vec2(uModel_to_NDC * vec3(aVertexPosition, 1.f)), 0.0, 1.0);
}
