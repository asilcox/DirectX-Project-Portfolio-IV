cbuffer cBuf
{
	matrix transform;
};

struct OutputVertex
{
	float3 color : COLOR;
	float4 pos : SV_POSITION;
};

OutputVertex main( float3 pos : POSITION, float3 color : COLOR )
{
	OutputVertex output;
	output.pos = mul(float4(pos, 1.0f), transform);
	output.color = color;
	return output;
}