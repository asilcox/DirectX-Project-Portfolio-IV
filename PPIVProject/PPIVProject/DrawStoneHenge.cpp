#include "DrawStoneHenge.h"

StoneHenge::StoneHenge(Graphics& gfx, float angle,
	float fov, float aspectRatio,
	float nearZ, float farZ, 
	float moveX, float moveY, float moveZ)
	:
	Object(gfx, angle, fov, aspectRatio, nearZ, farZ, moveX, moveY, moveZ)
{
	HRESULT hr;

	std::vector<OBJ_VERT> objVerts;

	for (int i = 0; i < 1457; ++i)
	{
		objVerts.push_back(StoneHenge_data[i]);
	}

	for (int i = 0; i < 2532; ++i)
	{
		indices.push_back(StoneHenge_indicies[i]);
	}

	VertexBuffer* vBuffer = new VertexBuffer(gfx, objVerts);
	vBuffer->SetVertexBuffer(gfx);
	delete vBuffer;

	IndexBuffer* iBuffer = new IndexBuffer(gfx, indices);
	iBuffer->SetIndexBuffer(gfx);
	delete iBuffer;

	const ConstantBufferMatrix cbMatrix[] =
	{
		{
			DirectX::XMMatrixTranspose(
				DirectX::XMMatrixTranslation(0.0f, -5.0f, 10.0f) *
				gfx.GetCamera() * gfx.GetProjection()
			)
		},
		{
		DirectX::XMMatrixTranspose(
			DirectX::XMMatrixIdentity() *
			DirectX::XMMatrixTranslation(0.0f, -5.0f, 10.0f)
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

	Texture* pTexture = new Texture(gfx, L"Images\\StoneHenge.dds");
	pTexture->SetTexture(gfx);
	delete pTexture;

	Sampler* pSampler = new Sampler(gfx);
	pSampler->SetSampler(gfx);
	delete pSampler;

	PixelShader* pShader = new PixelShader(gfx, L"TextureSpotPS.cso");
	pShader->SetPixelShader(gfx);
	delete pShader;

	VertexShader* vShader = new VertexShader(gfx, L"TextureSpotVS.cso");
	vShader->SetVertexShader(gfx);
	delete vShader;

	auto pvs = std::make_unique<VertexShader>(gfx, L"TextureSpotVS.cso");
	auto pvsbc = pvs->GetBytecode();

	const std::vector<D3D11_INPUT_ELEMENT_DESC> input =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	InputLayout* layout = new InputLayout(gfx, input, pvsbc);
	layout->SetInputLayout(gfx);
	delete layout;

	Topology* topology = new Topology(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	topology->SetTopology(gfx);
	delete topology;

	struct PSMaterialConstant
	{
		float specularIntensity = 0.6f;
		float specularPower = 30.0f;
		float padding[2];
	} colorConst;

	PixelConstantBuffer<PSMaterialConstant>* pixelConstantBuffer =
		new PixelConstantBuffer<PSMaterialConstant>(gfx, colorConst, 1);
	pixelConstantBuffer->SetPixelConstantBuffer(gfx);
	delete pixelConstantBuffer;
}

DirectX::XMMATRIX StoneHenge::GetTransformXM() const
{
	return DirectX::XMMatrixTranspose(
		DirectX::XMMatrixRotationZ(0.5f) *
		DirectX::XMMatrixRotationX(0.5f) *
		DirectX::XMMatrixTranslation(0.0f, 0.0f, 4.0f)) *
		DirectX::XMMatrixPerspectiveFovLH(1.0f, 1260.0f / 720.0f, 0.5f, 10.0f);
}

void StoneHenge::Update(Graphics& gfx, int chooseLight)
{
	if (chooseLight == 0)
	{
		PixelShader* pShader = new PixelShader(gfx, L"TextureDirectionalPS.cso");
		pShader->SetPixelShader(gfx);
		delete pShader;
	}

	if (chooseLight == 1)
	{
		PixelShader* pShader = new PixelShader(gfx, L"TexturePointPS.cso");
		pShader->SetPixelShader(gfx);
		delete pShader;
	}

	if (chooseLight == 2)
	{
		PixelShader* pShader = new PixelShader(gfx, L"TextureSpotPS.cso");
		pShader->SetPixelShader(gfx);
		delete pShader;
	}
}