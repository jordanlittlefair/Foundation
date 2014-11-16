cbuffer TransformMatrices_cbuffer : register(b0)
{
	struct TransformMatrices
	{
		float4x4 world_view_proj_matrix;
	};
	TransformMatrices transform_matrices;
};

struct VSInput
{
	float3 position : POSITION;
};

struct VSOutput
{
	float4 hposition: SV_Position;
};

VSOutput main( VSInput vertex )
{
	VSOutput output;
	
	output.hposition = mul( float4( vertex.position, 1.0f ), transform_matrices.world_view_proj_matrix );
			
	return output;
};