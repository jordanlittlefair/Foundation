struct VSInput
{
	uint id : SV_VertexID;
};

struct VSOutput
{
	float4 hposition: SV_Position;
};

static const float4 positions[6] =
{
	{ -1, 1, 0, 1 },
	{  1,  1, 0, 1 },
	{ -1,  -1, 0, 1 },
	{ 1, 1, 0, 1 },
	{  1, -1, 0, 1 },
	{  -1,  -1, 0, 1 }
};

VSOutput main( VSInput vertex )
{
	VSOutput output;
	
	output.hposition = positions[vertex.id];
	
	return output;
};