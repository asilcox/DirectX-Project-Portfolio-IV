#pragma once
#include "Graphics.h"

class PixelShader
{
public:
	PixelShader(Graphics& gfx, LPCWSTR pFileName)
	{
		D3DReadFileToBlob(pFileName, &pBlob);
		GetDevice(gfx)->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);
	}
	~PixelShader()
	{
		if (pPixelShader) pPixelShader->Release();
	}
	void SetPixelShader(Graphics& gfx);
	ID3D11DeviceContext* GetContext(Graphics& gfx);
	ID3D11Device* GetDevice(Graphics& gfx);
protected:
	ID3D11PixelShader* pPixelShader = nullptr;
	ID3DBlob* pBlob = nullptr;
};