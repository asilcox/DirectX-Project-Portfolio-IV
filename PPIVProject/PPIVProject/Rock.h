#pragma once
#include "Object.h"

class Rock
{
public:
	Rock();
	//DirectX::XMMATRIX GetTransformXM() const override;
	void Update(Graphics& gfx, float angle,
		float fov, float aspectRatio,
		float nearZ, float farZ);
	void LoadMesh(const char* filename);
	void Update(Graphics& gfx, int chooseLight);
	ID3D11DeviceContext* GetContext(Graphics& gfx);
	ID3D11Device* GetDevice(Graphics& gfx);
protected:
	Mesh rockMesh;
};