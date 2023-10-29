#version 450 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{    
   // vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
   // color = vec4(textColor, 1.0) * sampled;




    vec4 setColor = vec4(1.0f,1.0f,1.0f,texture(text, TexCoords));
//    setColor = 

//    vec4 sampled = vec4(1.0,1.0 , 1.0, texture(text , TexCoords).r);
 
   color = vec4(textColor, 1.0) * setColor;
}