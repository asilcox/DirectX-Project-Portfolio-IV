#pragma once
#include "Object.h"

class Cube : public Object
{
public:
	Cube(Graphics& gfx, float angle, 
		float fov, float aspectRatio,
		float nearZ, float farZ,
		float moveX, float moveY, float moveZ);
	void Update(Graphics& gfx, int chooseLight);
	DirectX::XMMATRIX GetTransformXM() const override;
private:
	DirectX::XMFLOAT3X3 mt;
};