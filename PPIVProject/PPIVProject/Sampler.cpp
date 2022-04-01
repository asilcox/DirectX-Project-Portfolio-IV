#include "Sampler.h"

Sampler::Sampler(Graphics& gfx)
{
	HRESULT hr;
	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	GetDevice(gfx)->CreateSamplerState(&samplerDesc, &pSampler);
}

void Sampler::SetSampler(Graphics& gfx)
{
	GetContext(gfx)->PSSetSamplers(0, 1, &pSampler);
}

ID3D11DeviceContext* Sampler::GetContext(Graphics& gfx)
{
	return gfx.pContext;
}

ID3D11Device* Sampler::GetDevice(Graphics& gfx)
{
	return gfx.pDevice;
}