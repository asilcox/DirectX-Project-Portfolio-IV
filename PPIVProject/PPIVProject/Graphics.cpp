#include <sstream>
#include <d3dcompiler.h>
#include <cmath>
#include "Graphics.h"
#include "BindableBase.h"
#include "Triangle.h"
#include "Rock.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

using namespace DirectX;

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

Graphics::Graphics(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC scd = {};
	scd.BufferDesc.Width = screenWidth;
	scd.BufferDesc.Height = screenHeight;
	scd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	scd.BufferDesc.RefreshRate.Numerator = 0;
	scd.BufferDesc.RefreshRate.Denominator = 0;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.BufferCount = 1;
	scd.OutputWindow = hWnd;
	scd.Windowed = TRUE;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	UINT creationFlags = 0;
#ifdef _DEBUG
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	HRESULT hr;

	D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
		0, nullptr, 0, D3D11_SDK_VERSION, &scd, &pSwap, &pDevice, nullptr, &pContext);

	ID3D11Resource* pBackBuffer = nullptr;
	hr = pSwap->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&pBackBuffer));
	if (pBackBuffer != 0)
		hr = pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &pTarget);
	pBackBuffer->Release();

	CD3D11_DEPTH_STENCIL_DESC depthDesc = {};
	depthDesc.DepthEnable = TRUE;
	depthDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthDesc.DepthFunc = D3D11_COMPARISON_LESS;
	ID3D11DepthStencilState* pDepthSState;
	hr = pDevice->CreateDepthStencilState(&depthDesc, &pDepthSState);

	pContext->OMSetDepthStencilState(pDepthSState, 1);

	ID3D11Texture2D* pDepthStencil;
	D3D11_TEXTURE2D_DESC descDepth = {};
	descDepth.Width = screenWidth;
	descDepth.Height = screenHeight;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	hr = pDevice->CreateTexture2D(&descDepth, nullptr, &pDepthStencil);

	CD3D11_DEPTH_STENCIL_VIEW_DESC depthSVD = {};
	depthSVD.Format = DXGI_FORMAT_D32_FLOAT;
	depthSVD.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthSVD.Texture2D.MipSlice = 0;
	if (pDepthStencil != 0)
		hr = pDevice->CreateDepthStencilView(pDepthStencil, &depthSVD, &pDepth);

	pContext->OMSetRenderTargets(1, &pTarget, pDepth);

	ImGui_ImplDX11_Init(pDevice, pContext);
	//D3D11_VIEWPORT viewport;
	//viewport.Width = screenWidth;
	//viewport.Height = screenHeight;
	//viewport.MinDepth = 0.0f;
	//viewport.MaxDepth = 1.0f;
	//viewport.TopLeftX = 0.0f;
	//viewport.TopLeftY = 0.0f;
	//pContext->RSSetViewports(1, &viewport);
}

Graphics::~Graphics()
{
	if (pTarget) pTarget->Release();
	if (pContext) pContext->Release();
	if (pSwap) pSwap->Release();
	if (pDevice) pDevice->Release();
	if (pDepth) pDepth->Release();

	ImGui_ImplDX11_Shutdown();
}

void Graphics::EndFrame()
{
	if (imguiEnabled)
	{
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	HRESULT hr;
	hr = pSwap->Present(1, 0);
}

void Graphics::ClearBuffer(float r, float g, float b)
{
	if (imguiEnabled)
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}

	const float color[] = { r, g, b, 1.0f };
	pContext->ClearRenderTargetView(pTarget, color);
	pContext->ClearDepthStencilView(pDepth, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Graphics::DrawObject(Object* obj)
{
	pContext->Draw((UINT)std::size(obj->GetVertices()), 0);
}

void Graphics::DrawIndexedObject(Object* obj)
{
	pContext->DrawIndexed((UINT)std::size(obj->GetIndices()), 0, 0);
}

void Graphics::DrawRock(Rock& rock)
{
	pContext->Draw(1500, 0);
}

float Graphics::GetScreenWidth()
{
	return screenWidth;
}

float Graphics::GetScreenHeight()
{
	return screenHeight;
}

void Graphics::SetScreenWidth(float sWidth)
{
	screenWidth = sWidth;
}

void Graphics::SetScreenHeight(float sHeight)
{
	screenHeight = sHeight;
}

void Graphics::SetViewport(int index)
{
	if (index == 0)
	{
		viewports[index].Width = screenWidth / 2;
		viewports[index].Height = screenHeight;
		viewports[index].MinDepth = 0.0f;
		viewports[index].MaxDepth = 1.0f;
		viewports[index].TopLeftX = 0.0f;
		viewports[index].TopLeftY = 0.0f;
	}

	if (index == 1)
	{
		viewports[index].Width = screenWidth / 2;
		viewports[index].Height = screenHeight;
		viewports[index].MinDepth = 0.0f;
		viewports[index].MaxDepth = 1.0f;
		viewports[index].TopLeftX = screenWidth / 2;
		viewports[index].TopLeftY = 0.0f;
	}

	pContext->RSSetViewports(1, &viewports[index]);
}

void Graphics::SetFullscreen(bool full)
{
	isFullscreen = full;
	pSwap->SetFullscreenState(isFullscreen, NULL);
}

bool Graphics::GetFullscreen()
{
	return isFullscreen;
}

void Graphics::SetCamera(DirectX::FXMMATRIX cam)
{
	camera = cam;
}

DirectX::XMMATRIX Graphics::GetCamera()
{
	return camera;
}

void Graphics::SetProjection(DirectX::FXMMATRIX proj)
{
	projection = proj;
}

DirectX::XMMATRIX Graphics::GetProjection()
{
	return projection;
}

void Graphics::EnableImgui()
{
	imguiEnabled = true;
}

void Graphics::DisableImgui()
{
	imguiEnabled = false;
}

bool Graphics::IsImguiEnabled()
{
	return imguiEnabled;
}

Camera* Graphics::GetCameraPos()
{
	return camPos;
}

void Graphics::SetCameraPos(Camera& cam)
{
	camPos = &cam;
}