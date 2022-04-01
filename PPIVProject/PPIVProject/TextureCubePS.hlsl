texture2D env : register(t0);

SamplerState envFilter : register(s0);

float4 main(float4 pos : SV_POSITION, float4 color : COLOR) : SV_TARGET
{
	return env.Sample(envFilter, color.xyz);
}