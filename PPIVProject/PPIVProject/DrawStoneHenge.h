#pragma once
#include "Object.h"
#include "StoneHenge.h"

class StoneHenge : public Object
{
public:
	StoneHenge(Graphics& gfx, float angle,
		float fov, float aspectRatio,
		float nearZ, float farZ,
		float moveX, float moveY, float moveZ);
	DirectX::XMMATRIX GetTransformXM() const override;
	void Update(Graphics& gfx, int chooseLight);
};