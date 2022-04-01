#include "Grid.h"

Grid::Grid(Graphics& gfx, float angle,
	float fov, float aspectRatio,
	float nearZ, float farZ)
	:
	Object(gfx, angle, fov, aspectRatio, nearZ, farZ, 0.0f, 0.0f, 0.0f)
{
	HRESULT hr;
	vertices.resize(10000);
	indices.resize(10000);
	int index = 0;
	for (int j = 0; j < 15; j++)
	{
		for (int i = 0; i < 15; i++)
		{
			// LINE 1
			// Upper left.
			vertices[index].pos = { (float)i, 0.0f, (float)(j + 1) };
			indices[index] = index;
			index++;

			// Upper right.
			vertices[index].pos = { (float)(i + 1), 0.0f, (float)(j + 1) };
			indices[index] = index;
			index++;

			// LINE 2
			// Upper right.
			vertices[index].pos = { (float)(i + 1), 0.0f, (float)(j + 1) };
			indices[index] = index;
			index++;

			// Bottom right.
			vertices[index].pos = { (float)(i + 1), 0.0f, (float)j };
			indices[index] = index;
			index++;

			// LINE 3
			// Bottom right.
			vertices[index].pos = { (float)(i + 1), 0.0f, (float)j };
			indices[index] = index;
			index++;

			// Bottom left.
			vertices[index].pos = { (float)i, 0.0f, (float)j };
			indices[index] = index;
			index++;

			// LINE 4
			// Bottom left.
			vertices[index].pos = { (float)i, 0.0f, (float)j };
			indices[index] = index;
			index++;

			// Upper left.
			vertices[index].pos = { (float)i, 0.0f, (float)(j + 1) };
			indices[index] = index;
			index++;
		}
	}

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
				DirectX::XMMatrixTranslation(-7.5f, -2.0f, 4.0f) *
				//DirectX::XMMatrixPerspectiveFovLH(1.0f, 630.0f / 720.0f, 0.5f, 100.0f)
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

	PixelShader* pShader = new PixelShader(gfx, L"GridPS.cso");
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
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	//InputLayout* layout = new InputLayout(gfx, input, pvsbc);
	//layout->SetInputLayout(gfx);
	//delete layout;

	Topology* topology = new Topology(gfx, D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	topology->SetTopology(gfx);
	delete topology;
}

DirectX::XMMATRIX Grid::GetTransformXM() const
{
	return DirectX::XMMatrixTranspose(
		DirectX::XMMatrixRotationZ(0.5f) *
		DirectX::XMMatrixRotationX(0.5f) *
		DirectX::XMMatrixTranslation(0.0f, 0.0f, 4.0f)) *
		DirectX::XMMatrixPerspectiveFovLH(1.0f, 1260.0f / 720.0f, 0.5f, 10.0f);
}