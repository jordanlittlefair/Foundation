cbuffer TransformMatrices : register(b0)
{
	float4x4 world_view_proj_matrix;
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
	
	output.hposition = mul( float4( vertex.position, 1.0f ), world_view_proj_matrix );
			
	return output;
};