#include "IndexBuffer.h"

ID3D11DeviceContext* IndexBuffer::GetContext(Graphics& gfx)
{
	return gfx.pContext;
}

ID3D11Device* IndexBuffer::GetDevice(Graphics& gfx)
{
	return gfx.pDevice;
}

void IndexBuffer::SetIndexBuffer(Graphics& gfx)
{
	GetContext(gfx)->IASetIndexBuffer(pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
}