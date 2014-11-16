cbuffer TransformMatrices_cbuffer : register(b0)
{
	struct TransformMatrices
	{
		float4x4 world_matrix;
		float4x4 view_matrix;
		float4x4 proj_matrix;
		float4x4 world_view_proj_matrix;
		// For velocity (motion blur)
		//float4x4 previous_world_view_proj_matrix;
	};
	TransformMatrices transform_matrices;	
};

struct VSInput
{
	float3 position: POSITION;
	float3 normal: NORMAL;
	float3 tangent: TANGENT;
	float3 binormal: BINORMAL;
	float2 texcoord: TEXCOORD;
};

struct VSOutput
{
	float4 hposition: SV_Position;
	float3 view_position: POSITION0;
	float3 view_normal: NORMAL;
	float3 view_tangent: TANGENT;
	float2 texcoord: TEXCOORD;
	
	//float4 now_hposition : POSITION1;
	//float4 previous_hposition : POSITION2;
};

VSOutput main( VSInput vertex )
{
	VSOutput output;
	
	float4x4 world_view_matrix = mul( transform_matrices.world_matrix, transform_matrices.view_matrix );
	
	output.hposition = mul( float4( vertex.position, 1.0f ), transform_matrices.world_view_proj_matrix );
	
	output.view_position = mul( float4( vertex.position, 1.0f ), world_view_matrix ).xyz;
	
	output.view_normal = normalize( mul( float4( vertex.normal, 0.0f ), world_view_matrix ).xyz );
	
	output.view_tangent = normalize( mul( float4( vertex.tangent, 0.0f ), world_view_matrix ).xyz );
		
	output.texcoord = vertex.texcoord;
	
	//output.now_hposition = mul( float4( vertex.position, 1.0f ), world_view_proj_matrix );
	//output.previous_hposition = mul( float4( vertex.position, 1.0f ), previous_world_view_proj_matrix );
	
	return output;
}