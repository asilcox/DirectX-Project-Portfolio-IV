#pragma once
#include <string>
#include <vector>

class MeshLoader
{
public:
	MeshLoader()
	{}
	Mesh LoadMesh(const char* filename, Mesh mesh)
	{
		std::vector<unsigned int> vIndices, uvIndices, normIndices;
		std::vector<DirectX::XMFLOAT4> tempVerts;
		std::vector<DirectX::XMFLOAT2> tempUVs;
		std::vector<DirectX::XMFLOAT4> tempNorms;

		FILE* file = fopen(filename, "r");
		if (file == NULL)
		{
			printf("Cannot load file.\n");
		}

		while (true)
		{
			char lineHeader[128];

			int res = fscanf(file, "%s", lineHeader);
			if (res == EOF)
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
			//myMesh.indicesList.resize(vIndices.size());
			//myMesh.vertexList.resize(vIndices.size());
			Vertex3D v;
			v.pos.x = tempVerts[vIndices[i] - 1].x;
			v.pos.y = tempVerts[vIndices[i] - 1].y;
			v.pos.z = tempVerts[vIndices[i] - 1].z;
			v.uv.u = tempUVs[uvIndices[i] - 1].x;
			v.uv.v = tempUVs[uvIndices[i] - 1].y;
			v.norm.x = tempNorms[normIndices[i] - 1].x;
			v.norm.y = tempNorms[normIndices[i] - 1].y;
			v.norm.z = tempNorms[normIndices[i] - 1].z;
			mesh.vertices.push_back(v);
			mesh.indices.push_back(i);
		}

		//for (int i = 0; i < vIndices.size(); ++i)
		//{
		//	myMesh.indicesList.resize(vIndices.size());
		//	myMesh.indicesList.push_back(vIndices[i]);
		//}
		return mesh;
	}
};