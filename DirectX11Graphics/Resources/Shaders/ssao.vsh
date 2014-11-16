struct VSInput
{
	uint id : SV_VertexID;
};

struct VSOutput
{
	float4 hposition: SV_Position;
	float2 texcoord: TEXCOORD;
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

static const float2 texcoords[6] = 
{
	{ 0, 0 },
	{ 1, 0 },
	{ 0, 1 },
	{ 1, 0 },
	{ 1, 1 },
	{ 0, 1 }
};

VSOutput main( VSInput vertex )
{
	VSOutput output;
	
	output.hposition = positions[vertex.id];
	output.texcoord = texcoords[vertex.id];
	
	return output;
};