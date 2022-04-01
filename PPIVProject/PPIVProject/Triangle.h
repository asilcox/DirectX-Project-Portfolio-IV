#pragma once
#include "Object.h"

class Triangle : public Object
{
public:
	Triangle(Graphics& gfx, float angle,
		float fov, float aspectRatio,
		float nearZ, float farZ);
	DirectX::XMMATRIX GetTransformXM() const override;
};