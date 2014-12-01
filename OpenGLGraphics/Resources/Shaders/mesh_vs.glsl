#version 330

uniform mat4 world_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;
uniform mat4 world_view_proj_matrix;

in vec3 position;
in vec3 normal;
in vec3 tangent;
in vec2 texcoord;

out vec3 world_position;
out vec3 world_normal;
out vec3 world_tangent;
out vec2 world_texcoord;

void main()
{
	gl_Position = world_view_proj_matrix * vec4( position, 1.0f );

	world_position = ( world_matrix * vec4( position, 1.0f ) ).xyz;
	world_normal = normalize( ( world_matrix * vec4( normal, 0.0f ) ).xyz );
	world_tangent = normalize( ( world_matrix * vec4( tangent, 0.0f ) ).xyz );
	
	world_texcoord = texcoord;
}