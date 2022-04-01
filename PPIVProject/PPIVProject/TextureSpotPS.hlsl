cbuffer LightCbuf
{
	float3 lightDir;
	float3 lightPos;
	float3 att;
	float3 ambient;
	float3 diffuseColor;
	float range;
	float cone;
};

cbuffer ObjectCbuf
{
	float specularIntensity;
	float specularPower;
	float padding[2];
};

Texture2D tex : register(t0);
SamplerState splr : register(s0);

float4 main(float3 worldPos : POSITION, float3 n : NORMAL, float2 tc : TEXCOORD) : SV_TARGET
{
	float3 finalColor = float3(0.0f, 0.0f, 0.0f);

	float3 vToL = lightPos - worldPos;
	float d = length(vToL);

	float3 finalAmbient = tex.Sample(splr, tc) * ambient;

	if (d > range)
		return float4(finalAmbient, 1.0f);

	vToL /= d;

	float amountofLight = dot(vToL, n);

	if (amountofLight > 0.0f)
	{
		finalColor += tex.Sample(splr, tc) * diffuseColor;
	
		finalColor /= (att.x + (att.y * d)) + (att.z * (d * d));

		finalColor *= pow(max(dot(-vToL, lightDir), 0.0f), cone);
	}

	finalColor = saturate(finalColor + finalAmbient);

	return float4(finalColor, 1.0f);
}