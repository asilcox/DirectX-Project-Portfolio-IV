#pragma once
#include "Graphics.h"
#include "ConstantBuffers.h"

class DirectionalLight
{
public:
	DirectionalLight(Graphics& gfx, float radius = 0.1f);
	void SpawnControlWindow();
	void SetDirectionalLight(Graphics& gfx, DirectX::FXMMATRIX view);
	void Reset();
private:
	struct DirectionalLightCBuf
	{
		alignas(16) DirectX::XMFLOAT3 dir;
		alignas(16) DirectX::XMFLOAT3 pos;
		alignas(16) DirectX::XMFLOAT3 ambient;
		alignas(16) DirectX::XMFLOAT3 diffuseColor;
		float diffuseIntensity;
		float attConst;
		float attLin;
		float attQuad;
	};
private:
	DirectionalLightCBuf cbData;
	mutable PixelConstantBuffer<DirectionalLightCBuf> cbuf;
};