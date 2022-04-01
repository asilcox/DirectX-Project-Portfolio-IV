#pragma once
#include "Graphics.h"
#include <vector>

class VertexBuffer
{
public:
	template<class V>
	VertexBuffer(Graphics& gfx, const std::vector<V>& vertices)
		:
		stride(sizeof(V))
	{
		D3D11_BUFFER_DESC bd = {};
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;
		bd.ByteWidth = UINT(sizeof(V) * vertices.size());
		bd.StructureByteStride = sizeof(V);
		D3D11_SUBRESOURCE_DATA sd = {};
		sd.pSysMem = vertices.data();
		GetDevice(gfx)->CreateBuffer(&bd, &sd, &pVertexBuffer);
	}
	~VertexBuffer()
	{
		if (pVertexBuffer) pVertexBuffer->Release();
	}
	void SetVertexBuffer(Graphics& gfx);
	static ID3D11DeviceContext* GetContext(Graphics& gfx);
	static ID3D11Device* GetDevice(Graphics& gfx);
protected:
	UINT stride;
	ID3D11Buffer* pVertexBuffer;
};