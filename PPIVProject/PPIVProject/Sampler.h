#pragma once
#include "Graphics.h"

class Sampler
{
public:
	Sampler(Graphics& gfx);
	~Sampler()
	{
		if (pSampler) pSampler->Release();
	}
	void SetSampler(Graphics& gfx);
	ID3D11DeviceContext* GetContext(Graphics& gfx);
	ID3D11Device* GetDevice(Graphics& gfx);
protected:
	ID3D11SamplerState* pSampler;
};