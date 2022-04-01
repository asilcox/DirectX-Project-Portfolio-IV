#include "Cube.h"
#include "AustinHead.h"

Cube::Cube(Graphics& gfx, float angle,
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
		{ { -0.5f, 0.5f, 0.5f }, { 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f } }, // 0
		{ { 0.5f, 0.5f, 0.5f }, { 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f } }, // 1
		{ { 0.5f, 0.5f, -0.5f }, { 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f } }, // 2
		{ { -0.5f, 0.5f, -0.5f }, { 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f } }, // 3

		// Bottom
		{ { -0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f }, { 0.0f, -1.0f, 0.0f } }, // 4
		{ { 0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f } }, // 5
		{ { 0.5f, -0.5f, 0.5f }, { 1.0f, 1.0f }, { 0.0f, -1.0f, 0.0f } }, // 6
		{ { -0.5f, -0.5f, 0.5f }, { 0.0f, 1.0f }, { 0.0f, -1.0f, 0.0f } }, // 7
		
		// Left
		{ { -0.5f, 0.5f, 0.5f }, { 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f } }, // 8
		{ { -0.5f, 0.5f, -0.5f }, { 1.0f, 0.0f }, { -1.0f, 0.0f, 0.0f } }, // 9
		{ { -0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f }, { -1.0f, 0.0f, 0.0f } }, // 10
		{ { -0.5f, -0.5f, 0.5f }, { 0.0f, 1.0f }, { -1.0f, 0.0f, 0.0f } }, // 11

		// Right
		{ { 0.5f, 0.5f, -0.5f }, { 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f } }, // 12
		{ { 0.5f, 0.5f, 0.5f }, { 1.0f, 0.0f }, { 1.0f, 0.0f, 0.0f } }, // 13
		{ { 0.5f, -0.5f, 0.5f }, { 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f } }, // 14
		{ { 0.5f, -0.5f, -0.5f }, { 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f } }, // 15

		// Front
		{ { -0.5f, 0.5f, -0.5f }, { 0.0f, 0.0f }, { 0.0f, 0.0f, -1.0f } }, // 16
		{ { 0.5f, 0.5f, -0.5f }, { 1.0f, 0.0f }, { 0.0f, 0.0f, -1.0f } }, // 17
		{ { 0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f }, { 0.0f, 0.0f, -1.0f } }, // 18
		{ { -0.5f, -0.5f, -0.5f }, { 0.0f, 1.0f }, { 0.0f, 0.0f, -1.0f } }, // 19

		// Back
		{ { 0.5f, 0.5f, 0.5f }, { 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } }, // 20
		{ { -0.5f, 0.5f, 0.5f }, { 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } }, // 21
		{ { -0.5f, -0.5f, 0.5f }, { 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f } }, // 22
		{ { 0.5f, -0.5f, 0.5f }, { 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f } } // 23
	};

	indices =
	{
		// Top
		0, 2, 3,  0, 1, 2,
		// Bottom
		4, 6, 7,  4, 5, 6,
		// Left
		8, 10, 11,  8, 9, 10,
		// Right
		12, 14, 15,  12, 13, 14,
		// Front
		16, 17, 18,  16, 18, 19,
		// Back
		20, 22, 23,  20, 21, 22
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
				//gfx.GetCamera() *
				DirectX::XMMatrixRotationZ(angle) *
				DirectX::XMMatrixRotationX(angle) *
				DirectX::XMMatrixTranslation(0.0f, 0.0f, 4.0f) *
				//DirectX::XMMatrixPerspectiveFovLH(fov, 630.0f / 720.0f, nearZ, farZ) * 
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

	//TransformCbuf* transform = new TransformCbuf(gfx, *this);
	//transform->SetVertexConstantBuffer(gfx);
	//delete transform;

	Texture* pTexture = new Texture(gfx, L"Images\\AustinHead.dds");
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

	//struct PSMaterialConstant
	//{
	//	float specularIntensity = 0.6f;
	//	float specularPower = 30.0f;
	//	float padding[2];
	//} colorConst;

	//PixelConstantBuffer<PSMaterialConstant>* pPixelCBuf = new PixelConstantBuffer<PSMaterialConstant>(gfx, colorConst, 1); 
	//pPixelCBuf->SetPixelConstantBuffer(gfx);

	DirectX::XMStoreFloat3x3(
		&mt,
		gfx.GetCamera()* gfx.GetProjection()
	);
}

DirectX::XMMATRIX Cube::GetTransformXM() const
{
	return DirectX::XMMatrixTranspose(
		DirectX::XMMatrixRotationZ(0.5f) *
		DirectX::XMMatrixRotationX(0.5f) *
		DirectX::XMMatrixTranslation(0.0f, 0.0f, 4.0f)) *
		DirectX::XMLoadFloat3x3(&mt);
		//DirectX::XMMatrixPerspectiveFovLH(1.0f, 630.0f / 720.0f, 0.5f, 50.0f));
}
//{
//	return DirectX::XMLoadFloat3x3(&mt) * Object::GetTransformXM();
//	//return DirectX::XMMatrixTranspose(
//		//DirectX::XMMatrixRotationZ(0.5f) *
//		//DirectX::XMMatrixRotationX(0.5f) *
//		//DirectX::XMMatrixTranslation(0.0f, 0.0f, 4.0f) *
//		//DirectX::XMMatrixPerspectiveFovLH(1.0f, 630.0f / 720.0f, 0.5f, 10.0f));
//}

void Cube::Update(Graphics& gfx, int chooseLight)
{
	if (chooseLight == 0)
	{
		PixelShader* pShader = new PixelShader(gfx, L"DirectionalLightPS.cso");
		pShader->SetPixelShader(gfx);
		delete pShader;
	}

	if (chooseLight == 1)
	{
		PixelShader* pShader = new PixelShader(gfx, L"TexturePS.cso");
		pShader->SetPixelShader(gfx);
		delete pShader;
	}

	if (chooseLight == 2)
	{
		PixelShader* pShader = new PixelShader(gfx, L"TexturePS.cso");
		pShader->SetPixelShader(gfx);
		delete pShader;
	}
}