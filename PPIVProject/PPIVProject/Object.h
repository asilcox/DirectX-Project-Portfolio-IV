#pragma once
#include "Graphics.h"
#include "BindableBase.h"
#include "Timer.h"

class Object
{
public:
	Object(Graphics& gfx, float angle, 
		float fov, float aspectRatio, 
		float nearZ, float farZ,
		float moveX, float moveY, float moveZ)
		:
		a(angle)
	{}
	ID3D11DeviceContext* GetContext(Graphics& gfx)
	{
		return gfx.pContext;
	}
	ID3D11Device* GetDevice(Graphics& gfx)
	{
		return gfx.pDevice;
	}
	std::vector<Vertex3D> GetVertices()
	{
		return vertices;
	}
	std::vector<unsigned short> GetIndices()
	{
		return indices;
	}
	virtual DirectX::XMMATRIX GetTransformXM() const = 0;
	//{
	//	return DirectX::XMMatrixTranspose(
	//		DirectX::XMMatrixRotationZ(0.5f) *
	//		DirectX::XMMatrixRotationX(0.5f) *
	//		DirectX::XMMatrixTranslation(0.0f, 0.0f, 4.0f)) *
	//		DirectX::XMMatrixPerspectiveFovLH(1.0f, 1260.0f / 720.0f, 0.5f, 10.0f);
	//}
protected:
	float a;
	std::vector<Vertex3D> vertices;
	std::vector<unsigned short> indices;
	Timer timer;
};