#include "Rock.h"
#include "MeshLoader.h"

Rock::Rock()
{
	LoadMesh("rock_03.obj");
}

void Rock::Update(Graphics& gfx, float angle,
	float fov, float aspectRatio,
	float nearZ, float farZ)
{
	VertexBuffer* vBuffer = new VertexBuffer(gfx, rockMesh.vertices);
	vBuffer->SetVertexBuffer(gfx);
	delete vBuffer;

	IndexBuffer* iBuffer = new IndexBuffer(gfx, rockMesh.indices);
	iBuffer->SetIndexBuffer(gfx);
	delete iBuffer;

	const ConstantBufferMatrix cbMatrix =
	{
		{
			DirectX::XMMatrixTranspose(
				DirectX::XMMatrixScaling(0.02f, 0.02f, 0.02f) *
				DirectX::XMMatrixTranslation(4.0f, -4.0f, 8.0f) *
				gfx.GetCamera() * gfx.GetProjection()

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

	Texture* pTexture = new Texture(gfx, L"Images\\rock_03.dds");
	pTexture->SetTexture(gfx);
	delete pTexture;

	Sampler* pSampler = new Sampler(gfx);
	pSampler->SetSampler(gfx);
	delete pSampler;

	PixelShader* pShader = new PixelShader(gfx, L"TexturePointPS.cso");
	pShader->SetPixelShader(gfx);
	delete pShader;

	VertexShader* vShader = new VertexShader(gfx, L"TexturePointVS.cso");
	vShader->SetVertexShader(gfx);
	delete vShader;

	auto pvs = std::make_unique<VertexShader>(gfx, L"TexturePointVS.cso");
	auto pvsbc = pvs->GetBytecode();

	const std::vector<D3D11_INPUT_ELEMENT_DESC> input =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
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

void Rock::LoadMesh(const char* filename)
{
	std::vector<unsigned int> vIndices, uvIndices, normIndices;
	std::vector<DirectX::XMFLOAT4> tempVerts;
	std::vector<DirectX::XMFLOAT2> tempUVs;
	std::vector<DirectX::XMFLOAT4> tempNorms;

	FILE* file = fopen("rock_03.obj", "r");
	if (file == NULL)
	{
		printf("Cannot load file.\n");
	}

	while (true)
	{
		char lineHeader[128];

		if (file != 0)
		{
			int res = fscanf(file, "%s", lineHeader);
			if (res == EOF)
				break;
		}
		else
			break;


		if (strcmp(lineHeader, "v") == 0)
		{
			DirectX::XMFLOAT4 v;
			fscanf(file, "%f %f %f\n", &v.x, &v.y, &v.z);
			tempVerts.push_back(v);
		}
		else if (strcmp(lineHeader, "vt") == 0)
		{
			DirectX::XMFLOAT2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			tempUVs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0)
		{
			DirectX::XMFLOAT4 norm;
			fscanf(file, "%f %f %f\n", &norm.x, &norm.y, &norm.z);
			tempNorms.push_back(norm);
		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			std::string v1, v2, v3;

			unsigned int vIndex[3], uvIndex[3], normIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vIndex[0], &uvIndex[0], &normIndex[0],
				&vIndex[1], &uvIndex[1], &normIndex[1], &vIndex[2], &uvIndex[2], &normIndex[2]);
			if (matches != 9)
			{
				printf("Can't be done with this parser.");
			}
			vIndices.push_back(vIndex[0]);
			vIndices.push_back(vIndex[1]);
			vIndices.push_back(vIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normIndices.push_back(normIndex[0]);
			normIndices.push_back(normIndex[1]);
			normIndices.push_back(normIndex[2]);
		}
	}

	for (int i = 0; i < vIndices.size(); ++i)
	{
		Vertex3D v;
		v.pos.x = tempVerts[vIndices[i] - 1].x;
		v.pos.y = tempVerts[vIndices[i] - 1].y;
		v.pos.z = tempVerts[vIndices[i] - 1].z;
		v.uv.u = tempUVs[uvIndices[i] - 1].x;
		v.uv.v = tempUVs[uvIndices[i] - 1].y;
		v.norm.x = tempNorms[normIndices[i] - 1].x;
		v.norm.y = tempNorms[normIndices[i] - 1].y;
		v.norm.z = tempNorms[normIndices[i] - 1].z;
		rockMesh.vertices.push_back(v);
	}

	//std::vector<Vertex3D> uniqueUVs;
	//std::vector<unsigned int> indicesList;
	//rockMesh.indices.resize(500);
	//float epsilon = 0.0001f;

	//for (int i = 0; i < tempUVs.size(); ++i)
	//{
	//	bool found = false;
	//	for (int j = 0; j < uniqueUVs.size(); ++j)
	//	{
	//		if (abs(tempUVs[i].x - uniqueUVs[j].uv.u) < epsilon &&
	//			abs(tempUVs[i].y - uniqueUVs[j].uv.v) < epsilon)
	//		{
	//			indicesList.push_back(j);
	//			found = true;
	//			break;
	//		}
	//	}

	//	if (!found)
	//	{
	//		uniqueUVs.push_back({ tempUVs[i].x, tempUVs[i].y });
	//		rockMesh.indices[i] = uniqueUVs.size() - 1;
	//	}
	//}

	//for (int i = 0; i < vIndices.size(); ++i)
	//{
	//	myMesh.indicesList.resize(vIndices.size());
	//	myMesh.indicesList.push_back(vIndices[i]);
	//}
}

ID3D11DeviceContext* Rock::GetContext(Graphics& gfx)
{
	return gfx.pContext;
}

ID3D11Device* Rock::GetDevice(Graphics& gfx)
{
	return gfx.pDevice;
}

//DirectX::XMMATRIX Rock::GetTransformXM() const
//{
//	return DirectX::XMMatrixTranspose(
//		DirectX::XMMatrixRotationZ(0.5f) *
//		DirectX::XMMatrixRotationX(0.5f) *
//		DirectX::XMMatrixTranslation(0.0f, 0.0f, 4.0f)) *
//		DirectX::XMMatrixPerspectiveFovLH(1.0f, 1260.0f / 720.0f, 0.5f, 10.0f);
//}

void Rock::Update(Graphics& gfx, int chooseLight)
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