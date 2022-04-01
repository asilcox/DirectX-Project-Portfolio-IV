cbuffer CBuf
{
	matrix modelView;
	matrix modelViewProj;
};

struct VSOut
{
	float3 worldPos : POSITION;
	float3 normal : NORMAL;
	float2 tc : TEXCOORD;
	float4 pos : SV_POSITION;
};

VSOut main(float3 pos : POSITION, float3 n : NORMAL, float2 tc : TEXCOORD)
{
	VSOut vso;
	vso.worldPos = (float3)mul(float4(pos, 1.0f), modelViewProj);
	vso.normal = mul(n, modelView);
	vso.pos = mul(float4(pos, 1.0f), modelView);
	vso.tc = tc;
	return vso;
}