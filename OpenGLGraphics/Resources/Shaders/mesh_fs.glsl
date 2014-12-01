#version 330

uniform vec4 colour;
uniform float translucency;

in vec3 world_position;
in vec3 world_normal;
in vec3 world_tangent;
in vec2 texcoord;

out vec3 world_position_out;
out vec4 world_normal_out;
out vec4 colour_out;

void main(void)
{
	world_position_out = world_position;
	world_normal_out = vec4( normalize(world_normal), colour.w );
	colour_out = vec4( colour.xyz, translucency );
}