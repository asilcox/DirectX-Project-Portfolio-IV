#pragma once
#include "Graphics.h"

class Texture
{
public:
	Texture(Graphics& gfx, const wchar_t* filename);
	~Texture()
	{
		if (pTexture) pTexture->Release();
		if (pTextureView) pTextureView->Release();
		if (pEnvironmentTexture) pEnvironmentTexture->Release();
		if (pEnvironmentTextureView) pEnvironmentTextureView->Release();
	}
	void SetTexture(Graphics& gfx);
	ID3D11DeviceContext* GetContext(Graphics& gfx);
	ID3D11Device* GetDevice(Graphics& gfx);
protected:
	ID3D11Texture2D* pTexture = nullptr;
	ID3D11Texture2D* pEnvironmentTexture = nullptr;
	ID3D11ShaderResourceView* pTextureView = nullptr;
	ID3D11ShaderResourceView* pEnvironmentTextureView = nullptr;
	int width;
	int height;
	unsigned int rowPitch;
};