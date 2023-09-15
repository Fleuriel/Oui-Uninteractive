/*!
@file		my-tutorial-3.frag
@author		pghali@digipen.edu
@co-author	zijun.tok@gmail.com
@date		05/25/2023

fragment shader file
*//*__________________________________________________________________________*/

#version 450 core

uniform vec3 uColor;

layout (location=0) out vec4 fFragColor;

void main()
{
	fFragColor = vec4(uColor, 1.0);
}