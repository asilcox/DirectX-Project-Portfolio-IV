#pragma once
#include "Graphics.h"
#include "ConstantBuffers.h"

class PointLight
{
public:
	PointLight(Graphics& gfx, float radius = 0.1f);
	void SpawnControlWindow();
	void SetPointLight(Graphics& gfx, DirectX::FXMMATRIX view);
	void Reset();
private:
	struct PointLightCBuf
	{
		alignas(16) DirectX::XMFLOAT3 pos;
		alignas(16) DirectX::XMFLOAT3 ambient;
		alignas(16) DirectX::XMFLOAT3 diffuseColor;
		float diffuseIntensity;
		float attConst;
		float attLin;
		float attQuad;
	};
private:
	PointLightCBuf cbData;
	mutable PixelConstantBuffer<PointLightCBuf> cbuf;
};