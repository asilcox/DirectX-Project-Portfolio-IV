#include "VertexBuffer.h"

ID3D11DeviceContext* VertexBuffer::GetContext(Graphics& gfx)
{
	return gfx.pContext;
}

ID3D11Device* VertexBuffer::GetDevice(Graphics& gfx)
{
	return gfx.pDevice;
}

void VertexBuffer::SetVertexBuffer(Graphics& gfx)
{
	const UINT offset = 0;
	GetContext(gfx)->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);
}