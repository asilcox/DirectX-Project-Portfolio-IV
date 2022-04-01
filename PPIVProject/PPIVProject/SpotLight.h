#pragma once
#include "Graphics.h"
#include "ConstantBuffers.h"

class SpotLight
{
public:
	SpotLight(Graphics& gfx);
	void SpawnPositionWindow();
	void SpawnDirectionWindow();
	void SetSpotLight(Graphics& gfx, DirectX::FXMMATRIX view);
	void Reset();
private:
	struct SpotLightCBuf
	{
		alignas(16) DirectX::XMFLOAT3 dir;
		alignas(16) DirectX::XMFLOAT3 pos;
		alignas(16) DirectX::XMFLOAT3 att;
		alignas(16) DirectX::XMFLOAT3 ambient;
		alignas(16)DirectX::XMFLOAT3 diffuseColor;
		float range;
		float cone;
	};
private:
	SpotLightCBuf cbData;
	mutable PixelConstantBuffer<SpotLightCBuf> cbuf;
};