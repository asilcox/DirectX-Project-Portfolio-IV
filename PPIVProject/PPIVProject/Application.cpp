#include "Application.h"
#include "Triangle.h"
#include "Cube.h"
#include "DrawStoneHenge.h"
#include "Rock.h"
#include "Grid.h"
#include "Skybox.h"
#include "ReflectiveCube.h"
#include "imgui/imgui.h"

Application::Application()
	:
	window(1280, 720, "My Window Box"),
	dLight(window.Gfx()),
	pLight(window.Gfx()),
	sLight(window.Gfx())
{
	//Rock rock(window.Gfx(), angle, fov, aspectRatio, nearZ, farZ);
	Cube cube(window.Gfx(), angle, fov, aspectRatio, nearZ, farZ,
		cam.GetPos().x, cam.GetPos().y, cam.GetPos().z);

	//rock = new Rock(window.Gfx(), angle, fov, aspectRatio, nearZ, farZ);

	objects.push_back(&cube);
	cubes.push_back(cube);

	window.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(screenWidth, screenHeight, nearZ, farZ));
}

int Application::Start()
{
	while (true)
	{
		if (const auto msgCode = Window::ProcessMessages())
			return *msgCode;

		DrawFrame();
	}
}

void Application::DrawFrame()
{
	const auto dt = timer.Mark();

	window.Gfx().ClearBuffer(0.0f, 0.1f, 0.2f);

	//DirectionalLight dLight(window.Gfx());
	window.Gfx().SetCamera(cam.GetMatrix());
	//window.Gfx().SetCameraPos(cam);

	if (chooseLight == 0)
		dLight.SetDirectionalLight(window.Gfx(), DirectX::XMMatrixIdentity());
	if (chooseLight == 1)
		pLight.SetPointLight(window.Gfx(), cam.GetMatrix());
	if (chooseLight == 2)
		sLight.SetSpotLight(window.Gfx(), cam.GetMatrix());
	AdjustCamera(dt);


	// Viewport 0
	window.Gfx().SetViewport(0);

	Cube cube(window.Gfx(), angle, fov, aspectRatio, nearZ, farZ, 
		cam.GetPos().x, cam.GetPos().y, cam.GetPos().z);
	cube.Update(window.Gfx(), chooseLight);
	window.Gfx().DrawIndexedObject(&cube);

	//window.Gfx().DrawRock(*rock);

	//window.Gfx().DrawIndexedObject(&rock);
	//window.Gfx().DrawIndexedObject(objects[0]);

	//window.Gfx().pContext->DrawIndexed((UINT)std::size(cubes[0].GetIndices()), 0, 0);

	Grid grid(window.Gfx(), angle, fov, aspectRatio, nearZ, farZ);
	window.Gfx().DrawObject(&grid);

	// Viewport 1
	window.Gfx().SetViewport(1);

	Skybox skybox(window.Gfx(), angle, fov, aspectRatio, nearZ, farZ,
		cam.GetPos().x, cam.GetPos().y, cam.GetPos().z);
	window.Gfx().DrawIndexedObject(&skybox);

	StoneHenge stone(window.Gfx(), angle, fov, aspectRatio, nearZ, farZ,
		cam.GetPos().x, cam.GetPos().y, cam.GetPos().z);
	stone.Update(window.Gfx(), chooseLight);
	window.Gfx().DrawIndexedObject(&stone);

	rock.Update(window.Gfx(), angle, fov, aspectRatio, nearZ, farZ);
	rock.Update(window.Gfx(), chooseLight);
	window.Gfx().DrawRock(rock);

	ReflectiveCube rCube(window.Gfx(), angle, fov, aspectRatio, nearZ, farZ);
	window.Gfx().DrawIndexedObject(&rCube);


	//if (toggle)
	//{
	//	DirectX::XMVECTOR eyePos = DirectX::XMVectorSet(cam.GetPos().x, cam.GetPos().y, cam.GetPos().z, 1.0f);
	//	DirectX::XMMatrixLookAtLH(eyePos, rCube.,{ 0.0f, 1.0f, 0.0f, 1.0f });
	//}

	dLight.SpawnControlWindow();
	pLight.SpawnControlWindow();
	sLight.SpawnPositionWindow();
	sLight.SpawnDirectionWindow();
	SpawnWindowManagerWindow();
	SpawnRenderManagerWindow();
	SpawnLightControlWindow();
	window.Gfx().SetProjection(DirectX::XMMatrixPerspectiveFovLH(fov, aspectRatio, nearZ, farZ));
	window.Gfx().EndFrame();
}

void Application::AdjustCamera(float dt)
{
	if (GetAsyncKeyState(0x57))
		cam.Translate({ 0.0f, 0.0f, dt });
	if (GetAsyncKeyState(0x41))
		cam.Translate({ -dt, 0.0f, 0.0f });
	if (GetAsyncKeyState(0x53))
		cam.Translate({ 0.0f, 0.0f, -dt });
	if (GetAsyncKeyState(0x44))
		cam.Translate({ dt, 0.0f, 0.0f });
	if (GetAsyncKeyState(VK_SPACE))
		cam.Translate({ 0.0f, dt, 0.0f });
	if (GetAsyncKeyState(VK_SHIFT))
		cam.Translate({ 0.0f, -dt, 0.0f });

	if (camdx >= 3.14159f)
		camdx = -3.0f;
	if (camdx <= -3.14159f)
		camdx = 3.0f;

	if (GetAsyncKeyState(VK_LEFT))
	{
		camdx -= 0.1f;
		cam.Rotate(camdx, camdy);
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		camdx += 0.1f;
		cam.Rotate(camdx, camdy);
	}
	if (GetAsyncKeyState(VK_UP) && camdy > -1.5f)
	{
		camdy -= 0.1f;
		cam.Rotate(camdx, camdy);
	}
	if (GetAsyncKeyState(VK_DOWN) && camdy < 1.5f)
	{
		camdy += 0.1f;
		cam.Rotate(camdx, camdy);
	}
}

void Application::SpawnRenderManagerWindow()
{
	if (ImGui::Begin("Render Controls"))
	{
		ImGui::SliderFloat("FOV", &fov, 0.5f, 2.0f, "%.4f", 1.0f);
		ImGui::SliderFloat("Near Z", &nearZ, 0.1f, 20.0f, "%.4f", 0.5f);
		ImGui::SliderFloat("Far Z", &farZ, 21.0f, 50.0f, "%.4f", 0.5f);
	}

	if (ImGui::Button("Look At Cube"))
		toggle = true;
	if (ImGui::Button("Stop Looking"))
		toggle = false;
	ImGui::End();
}

void Application::SpawnWindowManagerWindow()
{
	static bool isToggled = false;

	if (isToggled && !window.Gfx().GetFullscreen())
	{
		window.Gfx().SetFullscreen(true);
		Sleep(100);
	}
	if (!isToggled && window.Gfx().GetFullscreen())
	{
		window.Gfx().SetFullscreen(false);
		Sleep(100);
	}

	if (ImGui::Begin("Window Controls"))
	{
		if (ImGui::Button(" FullScreen Toggle ", ImVec2(250, 50)))
			isToggled = !isToggled;
	}
	ImGui::End();
}

void Application::SpawnLightControlWindow()
{
	if (ImGui::Begin("Choose Light"))
	{
		if (ImGui::Button("Directional"))
			chooseLight = 0;
		if (ImGui::Button("Point"))
			chooseLight = 1;
		if (ImGui::Button("Spot"))
			chooseLight = 2;
	}
	ImGui::End();
}


Application::~Application()
{}