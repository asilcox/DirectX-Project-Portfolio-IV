#pragma once
#include "Object.h"

class ReflectiveCube : public Object
{
public:
	ReflectiveCube(Graphics& gfx, float angle,
		float fov, float aspectRatio,
		float nearZ, float farZ);
	DirectX::XMMATRIX GetTransformXM() const override;
};