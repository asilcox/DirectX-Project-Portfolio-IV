#include "Topology.h"

Topology::Topology(Graphics& gfx, D3D11_PRIMITIVE_TOPOLOGY type)
	:
	type(type)
{}

ID3D11DeviceContext* Topology::GetContext(Graphics& gfx)
{
	return gfx.pContext;
}

ID3D11Device* Topology::GetDevice(Graphics& gfx)
{
	return gfx.pDevice;
}

void Topology::SetTopology(Graphics& gfx)
{
	GetContext(gfx)->IASetPrimitiveTopology(type);
}