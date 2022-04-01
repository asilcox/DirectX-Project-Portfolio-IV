#include "PixelShader.h"

ID3D11DeviceContext* PixelShader::GetContext(Graphics& gfx)
{
	return gfx.pContext;
}

ID3D11Device* PixelShader::GetDevice(Graphics& gfx)
{
	return gfx.pDevice;
}

void PixelShader::SetPixelShader(Graphics& gfx)
{
	GetContext(gfx)->PSSetShader(pPixelShader, nullptr, 0);
}