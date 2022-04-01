#pragma once
#include <DirectXMath.h>
#include <vector>

struct Vertex3D
{
	struct
	{
		float x;
		float y;
		float z;
	} pos;
	
	struct
	{
		float u;
		float v;
	} uv;

	struct
	{
		float x;
		float y;
		float z;
	} norm;
};

struct Mesh
{
	std::vector<Vertex3D> vertices;
	std::vector<unsigned short> indices;
};

struct ConstantBufferMatrix
{
	DirectX::XMMATRIX transform;
};

//struct Matricies
//{
//	DirectX::XMFLOAT4X4 worldMatrix;
//	DirectX::XMFLOAT4X4 viewMatrix;
//	DirectX::XMFLOAT4X4 projectionMatrix;
//}MyMatricies;