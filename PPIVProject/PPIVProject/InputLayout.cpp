#include "InputLayout.h"

InputLayout::InputLayout(Graphics& gfx,
	const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout,
	ID3DBlob* pVertexShaderByteCode)
{
	GetDevice(gfx)->CreateInputLayout(
		layout.data(), (UINT)layout.size(),
		pVertexShaderByteCode->GetBufferPointer(),
		pVertexShaderByteCode->GetBufferSize(),
		&pInputLayout
	);
}

ID3D11DeviceContext* InputLayout::GetContext(Graphics& gfx)
{
	return gfx.pContext;
}

ID3D11Device* InputLayout::GetDevice(Graphics& gfx)
{
	return gfx.pDevice;
}

void InputLayout::SetInputLayout(Graphics& gfx)
{
	GetContext(gfx)->IASetInputLayout(pInputLayout);
}