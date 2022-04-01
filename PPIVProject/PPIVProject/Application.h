#pragma once
#include "Timer.h"
#include "Window.h"
#include "ImguiManager.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Camera.h"
#include "Rock.h"
#include "Object.h"

class Application
{
public:
	Application();
	int Start();
	~Application();
private:
	void DrawFrame();
	void AdjustCamera(float dt);
	void SpawnRenderManagerWindow();
	void SpawnWindowManagerWindow();
	void SpawnLightControlWindow();
private:
	ImguiManager imgui;
	Window window;
	Timer timer;
	Camera cam;
	float camX = 0.0f;
	float camY = 0.0f;
	float camZ = 20.0f;
	float camdx = 0.0f;
	float camdy = 0.0f;
	float angle = 0.5f;
	float fov = 1.0f;
	float screenWidth = 1260.0f;
	float screenHeight = 720.0f;
	float aspectRatio = (0.5f * screenWidth / screenHeight);
	float nearZ = 0.5f;
	float farZ = 500.0f;

	std::vector<Object*> objects;
	Rock rock;
	std::vector<Cube> cubes;

	DirectionalLight dLight;
	PointLight pLight;
	SpotLight sLight;
	int chooseLight = 0;

	bool toggle = false;
};