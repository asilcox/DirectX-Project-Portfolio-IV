#pragma once
#include "Graphics.h"

class IndexBuffer
{
public:
	IndexBuffer(Graphics& gfx, const std::vector<unsigned short>& indices)
	{
		D3D11_BUFFER_DESC bd = {};
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;
		bd.ByteWidth = UINT(sizeof(unsigned short) * indices.size());
		bd.StructureByteStride = sizeof(unsigned short);
		D3D11_SUBRESOURCE_DATA sd = {};
		sd.pSysMem = indices.data();
		GetDevice(gfx)->CreateBuffer(&bd, &sd, &pIndexBuffer);
	}
	~IndexBuffer()
	{
		if (pIndexBuffer) pIndexBuffer->Release();
	}
	void SetIndexBuffer(Graphics& gfx);
	static ID3D11DeviceContext* GetContext(Graphics& gfx);
	static ID3D11Device* GetDevice(Graphics& gfx);
protected:
	ID3D11Buffer* pIndexBuffer;
};