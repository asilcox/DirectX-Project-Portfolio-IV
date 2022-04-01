#include "DirectionalLight.h"
#include "imgui/imgui.h"

DirectionalLight::DirectionalLight(Graphics& gfx, float radius)
	:
	cbuf(gfx)
{
	Reset();
}

void DirectionalLight::SpawnControlWindow()
{
	if (ImGui::Begin("Directional Light"))
	{
		ImGui::Text("Direction");
		ImGui::SliderFloat("X", &cbData.dir.x, -60.0f, 60.0f, "%.1f");
		ImGui::SliderFloat("Y", &cbData.dir.y, -60.0f, 60.0f, "%.1f");
		ImGui::SliderFloat("Z", &cbData.dir.z, -60.0f, 60.0f, "%.1f");

		if (ImGui::Button("Reset"))
			Reset();
	}
	ImGui::End();
}

void DirectionalLight::SetDirectionalLight(Graphics& gfx, DirectX::FXMMATRIX view)
{
	auto dataCopy = cbData;
	const auto pos = DirectX::XMLoadFloat3(&cbData.pos);
	DirectX::XMStoreFloat3(&dataCopy.pos, DirectX::XMVector3Transform(pos, DirectX::XMMatrixIdentity()));
	cbuf.Update(gfx, dataCopy);
	cbuf.SetPixelConstantBuffer(gfx);
}

void DirectionalLight::Reset()
{
	cbData = {
	{ -300.0f, 300.0f, -300.0f },
	{ -40.0f, 6.0f, 0.0f },
	{ 0.05f, 0.05f, 0.05f },
	{ 1.0f, 1.0f, 1.0f },
	0.7f,
	1.0f,
	0.045f,
	0.0075f,
	};
}