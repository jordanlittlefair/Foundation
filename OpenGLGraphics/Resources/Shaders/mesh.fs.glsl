#version 330

uniform vec4 colour;
uniform float translucency;

in vec3 view_position;
in vec3 view_normal;
in vec3 view_tangent;
in vec2 texcoord_out;

out vec4 geometry_out;
out vec4 diffuse_out;
out vec4 specular_out;

void main(void)
{
	geometry_out = vec4( view_normal, view_position.z );
	
	diffuse_out = vec4( 0.5, 0.5, 0.5, 0.5 );
	
	specular_out = vec4( 0.5, 0.5, 0.5, 0.5 );
}