#pragma once
#include "Graphics.h"

class Topology
{
public:
	Topology(Graphics& gfx, D3D11_PRIMITIVE_TOPOLOGY type);
	void SetTopology(Graphics& gfx);
	ID3D11DeviceContext* GetContext(Graphics& gfx);
	ID3D11Device* GetDevice(Graphics& gfx);
protected:
	D3D11_PRIMITIVE_TOPOLOGY type;
};