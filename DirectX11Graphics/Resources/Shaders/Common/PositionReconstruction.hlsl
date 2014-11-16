/*
	Buffers and Functions required to reconstruct a position from the depth buffer.

	Including shaders must define:
	
		POSITION_RECONSTRUCTION_BUFFER_INDEX
		
	Or the buffer will default to (b0)
*/

#ifndef POSITION_RECONSTRUCTION_BUFFER_INDEX
#define POSITION_RECONSTRUCTION_BUFFER_INDEX b0
#endif

/*
	Cbuffer containing the data required to reconstruct the position.
*/
cbuffer PositionReconstruction_cbuffer : register (POSITION_RECONSTRUCTION_BUFFER_INDEX)
{
	struct PositionReconstruction
	{
		float2 pr_screen_size;
		float pr_aspect_ratio;
		float pr_tan_half_fov_y;
	};
	PositionReconstruction position_reconstruction;
};

/*
	Create the position from the hposition.
*/
inline float3 GetPositionHpos( float4 hposition, float depth )
{
	const float2 t = float2(	hposition.x * 2 - position_reconstruction.pr_screen_size.x, 
								( position_reconstruction.pr_screen_size.y - hposition.y ) * 2 - position_reconstruction.pr_screen_size.y ) / position_reconstruction.pr_screen_size;
	
	const float2 tan_aspect = float2( position_reconstruction.pr_tan_half_fov_y * position_reconstruction.pr_aspect_ratio, position_reconstruction.pr_tan_half_fov_y );
	
	return float3( tan_aspect * t * depth, depth );
}

/*
	Create the position from a texcoord.
*/
inline float3 GetPositionTexcoord( float2 texcoord, float depth )
{
	const float2 t = float2(	texcoord.x * position_reconstruction.pr_screen_size.x * 2 - position_reconstruction.pr_screen_size.x, 
								( position_reconstruction.pr_screen_size.y - texcoord.y * position_reconstruction.pr_screen_size.y ) * 2 - position_reconstruction.pr_screen_size.y ) / position_reconstruction.pr_screen_size;
	
	const float2 tan_aspect = float2( position_reconstruction.pr_tan_half_fov_y * position_reconstruction.pr_aspect_ratio, position_reconstruction.pr_tan_half_fov_y );
	
	return float3( tan_aspect * t * depth, depth );
}