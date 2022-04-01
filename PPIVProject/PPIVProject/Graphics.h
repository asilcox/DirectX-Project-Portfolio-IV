#pragma once
#include "myMath.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <memory>
#include <random>

class Camera;
class Graphics
{
	friend class Application;

	friend class VertexBuffer;
	friend class IndexBuffer;
	friend class PixelShader;
	friend class VertexShader;
	friend class InputLayout;
	friend class Topology;
	friend class Sampler;
	friend class Texture;
	friend class Object;
	friend class Triangle;
	friend class Cube;
	friend class Rock;
	template<typename C>
	friend class ConstantBuffer;
public:
	Graphics(HWND hWnd);
	~Graphics();
	void EndFrame();
	void ClearBuffer(float r, float g, float b);
	float GetScreenWidth();
	float GetScreenHeight();
	void SetScreenWidth(float sWidth);
	void SetScreenHeight(float sHeight);
	void DrawObject(Object* obj);
	void DrawRock(Rock& rock);
	void DrawIndexedObject(Object* obj);
	void SetViewport(int index);
	void SetFullscreen(bool full);
	bool GetFullscreen();
	void SetCamera(DirectX::FXMMATRIX cam);
	DirectX::XMMATRIX GetCamera();
	Camera* GetCameraPos();
	void SetCameraPos(Camera& cam);
	void SetProjection(DirectX::FXMMATRIX proj);
	DirectX::XMMATRIX GetProjection();
	void EnableImgui();
	void DisableImgui();
	bool IsImguiEnabled();
private:
	ID3D11Device* pDevice = nullptr;
	IDXGISwapChain* pSwap = nullptr;
	ID3D11DeviceContext* pContext = nullptr;
	ID3D11RenderTargetView* pTarget = nullptr;
	ID3D11DepthStencilView* pDepth = nullptr;

	D3D11_VIEWPORT viewports[2];
	float screenWidth = 1280.0f;
	float screenHeight = 720.0f;

	bool isFullscreen = false;

	DirectX::XMMATRIX camera;
	DirectX::XMMATRIX projection;

	bool imguiEnabled = true;

	Camera* camPos;
};