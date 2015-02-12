#version 330

uniform mat4 world_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;
uniform mat4 world_view_proj_matrix;

in vec3 position;
in vec3 normal;
in vec3 tangent;
in vec3 binormal;
in vec2 texcoord_in;

out vec3 view_position;
out vec3 view_normal;
out vec3 view_tangent;
out vec2 texcoord_out;

void main()
{
	mat4 world_view_matrix = world_matrix * view_matrix;
			
	gl_Position = world_view_proj_matrix * vec4( position, 1.0f );

	view_position = ( world_view_matrix * vec4( position, 1.0f ) ).xyz;
	view_normal = normalize( ( world_view_matrix * vec4( normal, 0.0f ) ).xyz );
	view_tangent = normalize( ( world_view_matrix * vec4( tangent, 0.0f ) ).xyz );
	
	texcoord_out = texcoord_in;
}