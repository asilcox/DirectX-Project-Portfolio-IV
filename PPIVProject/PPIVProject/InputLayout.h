#pragma once
#include "Graphics.h"

class InputLayout
{
public:
	InputLayout(Graphics& gfx,
		const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout,
		ID3DBlob* pVertexShaderBytecode);
	~InputLayout()
	{
		if (pInputLayout) pInputLayout->Release();
	}
	void SetInputLayout(Graphics& gfx);
	ID3D11DeviceContext* GetContext(Graphics& gfx);
	ID3D11Device* GetDevice(Graphics& gfx);
protected:
	ID3D11InputLayout* pInputLayout = nullptr;
};