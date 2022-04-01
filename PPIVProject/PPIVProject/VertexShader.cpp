#include "VertexShader.h"

ID3D11DeviceContext* VertexShader::GetContext(Graphics& gfx)
{
	return gfx.pContext;
}

ID3D11Device* VertexShader::GetDevice(Graphics& gfx)
{
	return gfx.pDevice;
}

void VertexShader::SetVertexShader(Graphics& gfx)
{
	GetContext(gfx)->VSSetShader(pVertexShader, nullptr, 0);
}

ID3DBlob* VertexShader::GetBytecode()
{
	return pBlob;
}