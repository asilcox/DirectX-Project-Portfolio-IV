#include "Skybox.h"

Skybox::Skybox(Graphics& gfx, float angle,
	float fov, float aspectRatio,
	float nearZ, float farZ,
	float moveX, float moveY, float moveZ)
	:
	Object(gfx, angle, fov, aspectRatio, nearZ, farZ, moveX, moveY, moveZ)
{
	HRESULT hr;

	vertices =
	{
		// Top
		{ { -0.5f, 0.5f, 0.5f }, { 0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f } }, // 0
		{ { 0.5f, 0.5f, 0.5f }, { 0.25f, 0.0f }, { 0.0f, 1.0f, 0.0f } }, // 1
		{ { 0.5f, 0.5f, -0.5f }, { 0.25f, 1 / 3.0f }, { 0.0f, 1.0f, 0.0f } }, // 2
		{ { -0.5f, 0.5f, -0.5f }, { 0.5f, 1 / 3.0f }, { 0.0f, 1.0f, 0.0f } }, // 3

		// Bottom
		{ { -0.5f, -0.5f, -0.5f }, { 0.5f, 2 / 3.0f }, { 0.0f, -1.0f, 0.0f } }, // 4
		{ { 0.5f, -0.5f, -0.5f }, { 0.25f, 2 / 3.0f }, { 0.0f, -1.0f, 0.0f } }, // 5
		{ { 0.5f, -0.5f, 0.5f }, { 0.25f, 1.0f }, { 0.0f, -1.0f, 0.0f } }, // 6
		{ { -0.5f, -0.5f, 0.5f }, { 0.5f, 1.0f }, { 0.0f, -1.0f, 0.0f } }, // 7

		// Left
		{ { -0.5f, 0.5f, 0.5f }, { 0.75f, 1 / 3.0f }, { -1.0f, 0.0f, 0.0f } }, // 8
		{ { -0.5f, 0.5f, -0.5f }, { 0.5f, 1 / 3.0f }, { -1.0f, 0.0f, 0.0f } }, // 9
		{ { -0.5f, -0.5f, -0.5f }, { 0.5f, 2 / 3.0f }, { -1.0f, 0.0f, 0.0f } }, // 10
		{ { -0.5f, -0.5f, 0.5f }, { 0.75f, 2 / 3.0f }, { -1.0f, 0.0f, 0.0f } }, // 11

		// Right
		{ { 0.5f, 0.5f, -0.5f }, { 0.25f, 1 / 3.0f }, { 1.0f, 0.0f, 0.0f } }, // 12
		{ { 0.5f, 0.5f, 0.5f }, { 0.0f, 1 / 3.0f }, { 1.0f, 0.0f, 0.0f } }, // 13
		{ { 0.5f, -0.5f, 0.5f }, { 0.0f, 2 / 3.0f }, { 1.0f, 0.0f, 0.0f } }, // 14
		{ { 0.5f, -0.5f, -0.5f }, { 0.25f, 2 / 3.0f }, { 1.0f, 0.0f, 0.0f } }, // 15

		// Front
		{ { -0.5f, 0.5f, -0.5f }, { 0.5f, 1 / 3.0f }, { 0.0f, 0.0f, -1.0f } }, // 16
		{ { 0.5f, 0.5f, -0.5f }, { 0.25f, 1 / 3.0f }, { 0.0f, 0.0f, -1.0f } }, // 17
		{ { 0.5f, -0.5f, -0.5f }, { 0.25f, 2 / 3.0f }, { 0.0f, 0.0f, -1.0f } }, // 18
		{ { -0.5f, -0.5f, -0.5f }, { 0.5f, 2 / 3.0f }, { 0.0f, 0.0f, -1.0f } }, // 19

		// Back
		{ { 0.5f, 0.5f, 0.5f }, { 1.0f, 1 / 3.0f }, { 0.0f, 0.0f, 1.0f } }, // 20
		{ { -0.5f, 0.5f, 0.5f }, { 0.75f, 1 / 3.0f }, { 0.0f, 0.0f, 1.0f } }, // 21
		{ { -0.5f, -0.5f, 0.5f }, { 0.75f, 2 / 3.0f }, { 0.0f, 0.0f, 1.0f } }, // 22
		{ { 0.5f, -0.5f, 0.5f }, { 1.0f, 2 / 3.0f }, { 0.0f, 0.0f, 1.0f } } // 23
	};

	indices =
	{
		// Top
		1, 3, 2,  1, 0, 3,
		// Bottom
		5, 7, 6,  5, 4, 7,
		// Left
		9, 11, 10,  9, 8, 11,
		// Right
		13, 15, 14,  13, 12, 15,
		// Front
		17, 19, 18,  17, 16, 19,
		// Back
		21, 23, 22,  21, 20, 23
	};

	VertexBuffer* vBuffer = new VertexBuffer(gfx, vertices);
	vBuffer->SetVertexBuffer(gfx);
	delete vBuffer;

	IndexBuffer* iBuffer = new IndexBuffer(gfx, indices);
	iBuffer->SetIndexBuffer(gfx);
	delete iBuffer;

	const ConstantBufferMatrix cbMatrix =
	{
		{
			DirectX::XMMatrixTranspose(
				//DirectX::XMMatrixRotationY(0.05f) *
				DirectX::XMMatrixScaling(300.0f, 300.0f, 300.0f) *
				DirectX::XMMatrixTranslation(moveX, moveY, moveZ) *
				gfx.GetCamera() *
				//DirectX::XMMatrixPerspectiveFovLH(1.0f, 630.0f / 720.0f, 1.5f, 500.0f) * 
				gfx.GetProjection()
			)
		}
	};

	ID3D11Buffer* pConstantBufferMatrix;
	D3D11_BUFFER_DESC cbdMatrix;
	cbdMatrix.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbdMatrix.Usage = D3D11_USAGE_DYNAMIC;
	cbdMatrix.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbdMatrix.MiscFlags = 0;
	cbdMatrix.ByteWidth = sizeof(cbMatrix);
	cbdMatrix.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA csdMatrix = {};
	csdMatrix.pSysMem = &cbMatrix;
	GetDevice(gfx)->CreateBuffer(&cbdMatrix, &csdMatrix, &pConstantBufferMatrix);

	GetContext(gfx)->VSSetConstantBuffers(0, 1, &pConstantBufferMatrix);

	Texture* pTexture = new Texture(gfx, L"Images\\Texture2.dds");
	pTexture->SetTexture(gfx);
	delete pTexture;

	Sampler* pSampler = new Sampler(gfx);
	pSampler->SetSampler(gfx);
	delete pSampler;

	PixelShader* pShader = new PixelShader(gfx, L"TexturePS.cso");
	pShader->SetPixelShader(gfx);
	delete pShader;

	VertexShader* vShader = new VertexShader(gfx, L"TextureVS.cso");
	vShader->SetVertexShader(gfx);
	delete vShader;

	auto pvs = std::make_unique<VertexShader>(gfx, L"TextureVS.cso");
	auto pvsbc = pvs->GetBytecode();

	const std::vector<D3D11_INPUT_ELEMENT_DESC> input =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	InputLayout* layout = new InputLayout(gfx, input, pvsbc);
	layout->SetInputLayout(gfx);
	delete layout;

	Topology* topology = new Topology(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	topology->SetTopology(gfx);
	delete topology;
}

DirectX::XMMATRIX Skybox::GetTransformXM() const
{
	return DirectX::XMMatrixTranspose(
		DirectX::XMMatrixRotationZ(0.5f) *
		DirectX::XMMatrixRotationX(0.5f) *
		DirectX::XMMatrixTranslation(0.0f, 0.0f, 4.0f)) *
		DirectX::XMLoadFloat3x3(&mt);
	//DirectX::XMMatrixPerspectiveFovLH(1.0f, 630.0f / 720.0f, 0.5f, 50.0f));
}