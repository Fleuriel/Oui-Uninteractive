#version 450 core

layout (location=1) in vec2 vTexCoord; // Corrected attribute name
in vec3 FragPos;


layout (location=0) out vec4 fFragColor;

layout (location=0) in vec2 aVertexPosition;

uniform sampler2D uTex2d;

uniform vec3 ambient_light;
uniform vec3 point_light_pos;
uniform vec3 point_light_col;
uniform float point_light_intensity;

void main() 
{
    vec4 frag_color = texture(uTex2d, vTexCoord); // Corrected variable name
    if (frag_color.a < 1.0)
        discard;

    float distance = distance(point_light_pos.xy, FragPos.xy);
    float diffuse = 0.0;

    if (distance <= point_light_intensity)
        diffuse = 1.0 - abs(distance / point_light_intensity);

    vec3 lighting = (point_light_col * diffuse) + ambient_light;

    fFragColor = vec4(min(frag_color.rgb * lighting, frag_color.rgb), 1.0);
//     gl_FragColor = vec4(min(frag_color.rgb * lighting, frag_color.rgb), 1.0);
}