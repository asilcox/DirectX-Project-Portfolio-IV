#pragma once
#include "ConstantBuffers.h"
#include "Object.h"
#include <DirectXMath.h>

class TransformCbuf
{
private:
	struct Transforms
	{
		DirectX::XMMATRIX modelViewProj;
		DirectX::XMMATRIX model;
	};
public:
	TransformCbuf(Graphics& gfx, const Object& parent, UINT slot = 0);
	void SetVertexConstantBuffer(Graphics& gfx);
private:
	static std::unique_ptr<VertexConstantBuffer<Transforms>> pVcbuf;
	const Object& parent;
};