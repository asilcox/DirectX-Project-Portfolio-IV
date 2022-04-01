#pragma once
#include "Graphics.h"

class VertexShader
{
public:
	VertexShader(Graphics& gfx, LPCWSTR pFileName)
	{
		D3DReadFileToBlob(pFileName, &pBlob);
		GetDevice(gfx)->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);
	}
	~VertexShader()
	{
		if (pVertexShader) pVertexShader->Release();
	}
	void SetVertexShader(Graphics& gfx);
	ID3D11DeviceContext* GetContext(Graphics& gfx);
	ID3D11Device* GetDevice(Graphics& gfx);
	ID3DBlob* GetBytecode();
protected:
	ID3D11VertexShader* pVertexShader = nullptr;
	ID3DBlob* pBlob = nullptr;
};