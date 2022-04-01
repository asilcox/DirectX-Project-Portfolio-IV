#pragma once
#include "Object.h"

class Grid : public Object
{
public:
	Grid(Graphics& gfx, float angle,
		float fov, float aspectRatio,
		float nearZ, float farZ);
	DirectX::XMMATRIX GetTransformXM() const override;
};