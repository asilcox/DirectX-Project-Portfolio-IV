#include "TransformCbuf.h"

TransformCbuf::TransformCbuf(Graphics& gfx, const Object& parent, UINT slot)
	:
	parent(parent)
{
	if (!pVcbuf)
		pVcbuf = std::make_unique<VertexConstantBuffer<Transforms>>(gfx, slot);
}

void TransformCbuf::SetVertexConstantBuffer(Graphics& gfx)
{
	const auto modelView = parent.GetTransformXM() * gfx.GetCamera();
	const Transforms tf =
	{
		DirectX::XMMatrixTranspose(modelView),
		DirectX::XMMatrixTranspose(
			modelView *
			gfx.GetProjection()
		)
	};
	pVcbuf->Update(gfx, tf);
	pVcbuf->SetVertexConstantBuffer(gfx);
}

std::unique_ptr<VertexConstantBuffer<TransformCbuf::Transforms>> TransformCbuf::pVcbuf;