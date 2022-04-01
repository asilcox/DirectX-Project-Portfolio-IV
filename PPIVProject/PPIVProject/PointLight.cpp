#include "PointLight.h"
#include "imgui/imgui.h"

PointLight::PointLight(Graphics& gfx, float radius)
	:
	cbuf(gfx)
{
	Reset();
}

void PointLight::SpawnControlWindow()
{
	if (ImGui::Begin("Point Light"))
	{
		ImGui::Text("Position");
		ImGui::SliderFloat("X", &cbData.pos.x, -60.0f, 60.0f, "%.1f");
		ImGui::SliderFloat("Y", &cbData.pos.y, -60.0f, 60.0f, "%.1f");
		ImGui::SliderFloat("Z", &cbData.pos.z, -60.0f, 60.0f, "%.1f");

		if (ImGui::Button("Reset"))
			Reset();
	}
	ImGui::End();
}

void PointLight::SetPointLight(Graphics& gfx, DirectX::FXMMATRIX view)
{
	auto dataCopy = cbData;
	const auto pos = DirectX::XMLoadFloat3(&cbData.pos);
	DirectX::XMStoreFloat3(&dataCopy.pos, DirectX::XMVector3Transform(pos, DirectX::XMMatrixIdentity()));
	cbuf.Update(gfx, dataCopy);
	cbuf.SetPixelConstantBuffer(gfx);
}

void PointLight::Reset()
{
	cbData = {
	{ 0.0f, 0.0f, 0.0f },
	{ 0.05f, 0.05f, 0.05f },
	{ 1.0f, 0.7f, 0.8f },
	2.0f,
	1.0f,
	0.045f,
	0.0075f,
	};
}