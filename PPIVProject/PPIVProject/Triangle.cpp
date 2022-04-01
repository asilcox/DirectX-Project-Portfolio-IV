#include "Triangle.h"

Triangle::Triangle(Graphics& gfx, float angle,
	float fov, float aspectRatio,
	float nearZ, float farZ)
	:
	Object(gfx, angle, fov, aspectRatio, nearZ, farZ, 0.0f, 0.0f, 0.0f)
{
	HRESULT hr;

	vertices =
	{
		{ {}, {} },
		{ {}, {} },
		{ {} , {} }
	};

	indices =
	{
		0, 1, 2
	};

	VertexBuffer* vBuffer = new VertexBuffer(gfx, vertices);
	vBuffer->SetVertexBuffer(gfx);
	delete vBuffer;

	IndexBuffer* iBuffer = new IndexBuffer(gfx, indices);
	iBuffer->SetIndexBuffer(gfx);
	delete iBuffer;

	PixelShader* pShader = new PixelShader(gfx, L"PixelShader.cso");
	pShader->SetPixelShader(gfx);
	delete pShader;

	VertexShader* vShader = new VertexShader(gfx, L"VertexShader.cso");
	vShader->SetVertexShader(gfx);
	delete vShader;

	auto pvs = std::make_unique<VertexShader>(gfx, L"VertexShader.cso");
	auto pvsbc = pvs->GetBytecode();

	const std::vector<D3D11_INPUT_ELEMENT_DESC> input =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	InputLayout* layout = new InputLayout(gfx, input, pvsbc);
	layout->SetInputLayout(gfx);
	delete layout;

	Topology* topology = new Topology(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	topology->SetTopology(gfx);
	delete topology;
}

DirectX::XMMATRIX Triangle::GetTransformXM() const
{
	return DirectX::XMMatrixTranspose(
		DirectX::XMMatrixRotationZ(0.5f) *
		DirectX::XMMatrixRotationX(0.5f) *
		DirectX::XMMatrixTranslation(0.0f, 0.0f, 4.0f)) *
		DirectX::XMMatrixPerspectiveFovLH(1.0f, 1260.0f / 720.0f, 0.5f, 10.0f);
}