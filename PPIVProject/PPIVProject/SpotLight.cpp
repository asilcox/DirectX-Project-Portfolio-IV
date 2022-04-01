#include "SpotLight.h"
#include "imgui/imgui.h"

SpotLight::SpotLight(Graphics& gfx)
	:
	cbuf(gfx)
{
	Reset();
}

void SpotLight::SpawnPositionWindow()
{
	if (ImGui::Begin("Spot Light Position"))
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

void SpotLight::SpawnDirectionWindow()
{
	if (ImGui::Begin("Spot Light Direction"))
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

void SpotLight::SetSpotLight(Graphics& gfx, DirectX::FXMMATRIX view)
{
	auto dataCopy = cbData;
	auto pos = DirectX::XMLoadFloat3(&cbData.pos);
	DirectX::XMStoreFloat3(&dataCopy.pos, DirectX::XMVector3Transform(pos, DirectX::XMMatrixIdentity()));//gfx.GetCamera() * gfx.GetProjection()));
	cbuf.Update(gfx, dataCopy);
	cbuf.SetPixelConstantBuffer(gfx);
}

void SpotLight::Reset()
{
	cbData = {
		{ 0.0f, -1.0f, 0.0f },
		{ 1.0f, 30.0f, 1.0f },
		{ 0.4f, 0.02f, 0.0f },
		{ 0.2f, 0.2f, 0.2f },
		{ 0.0f, 1.0f, 1.0f },
		1000.0f,
		20.0f
	};
}