#pragma once
#include "Graphics.h"

template<typename C>
class ConstantBuffer
{
public:
	void Update(Graphics& gfx, const C& consts)
	{
		D3D11_MAPPED_SUBRESOURCE msr;
		GetContext(gfx)->Map(
			pConstantBuffer, 0u,
			D3D11_MAP_WRITE_DISCARD, 0u,
			&msr
		);
		memcpy(msr.pData, &consts, sizeof(consts));
		GetContext(gfx)->Unmap(pConstantBuffer, 0u);
	}
	ConstantBuffer(Graphics& gfx, const C& consts, UINT slot = 0)
		:
		slot(slot)
	{
		D3D11_BUFFER_DESC cbd;
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.MiscFlags = 0u;
		cbd.ByteWidth = sizeof(consts);
		cbd.StructureByteStride = 0u;

		D3D11_SUBRESOURCE_DATA csd = {};
		csd.pSysMem = &consts;
		GetDevice(gfx)->CreateBuffer(&cbd, &csd, &pConstantBuffer);
	}
	ConstantBuffer(Graphics& gfx, UINT slot = 0)
		:
		slot(slot)
	{
		D3D11_BUFFER_DESC cbd;
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.MiscFlags = 0u;
		cbd.ByteWidth = sizeof(C);
		cbd.StructureByteStride = 0u;
		GetDevice(gfx)->CreateBuffer(&cbd, nullptr, &pConstantBuffer);
	}
	ID3D11DeviceContext* GetContext(Graphics& gfx)
	{
		return gfx.pContext;
	}
	ID3D11Device* GetDevice(Graphics& gfx)
	{
		return gfx.pDevice;
	}
protected:
	ID3D11Buffer* pConstantBuffer;
	UINT slot;
};

template<typename C>
class VertexConstantBuffer : public ConstantBuffer<C>
{
	using ConstantBuffer<C>::pConstantBuffer;
	using ConstantBuffer<C>::slot;
	using ConstantBuffer<C>::GetContext;
public:
	using ConstantBuffer<C>::ConstantBuffer;
	void SetVertexConstantBuffer(Graphics& gfx)
	{
		GetContext(gfx)->VSSetConstantBuffers(slot, 1, &pConstantBuffer);
	}
};

template<typename C>
class PixelConstantBuffer : public ConstantBuffer<C>
{
	using ConstantBuffer<C>::pConstantBuffer;
	using ConstantBuffer<C>::slot;
	using ConstantBuffer<C>::GetContext;
public:
	using ConstantBuffer<C>::ConstantBuffer;
	void SetPixelConstantBuffer(Graphics& gfx)
	{
		GetContext(gfx)->PSSetConstantBuffers(slot, 1, &pConstantBuffer);
	}
};