#pragma once
#include "Object.h"

class Skybox : public Object
{
public:
	Skybox(Graphics& gfx, float angle,
		float fov, float aspectRatio,
		float nearZ, float farZ,
		float moveX, float moveY, float moveZ);
	DirectX::XMMATRIX GetTransformXM() const override;
private:
	DirectX::XMFLOAT3X3 mt;
};