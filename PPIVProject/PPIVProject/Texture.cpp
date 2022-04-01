#include "Texture.h"
#include <stdio.h>
#include "AustinHead.h"
#include "StoneHenge_Texture.h"
#include "DDSTextureLoader.h"

Texture::Texture(Graphics& gfx, const wchar_t* filename)
{
	//D3D11_TEXTURE2D_DESC textureDesc = {};
	////textureDesc.Width = StoneHenge_width;
	//textureDesc.Width = AustinHead_width;
	////textureDesc.Height = StoneHenge_height;
	//textureDesc.Height = AustinHead_height;
	//textureDesc.MipLevels = AustinHead_numlevels;
	//textureDesc.ArraySize = 1;
	//textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//textureDesc.SampleDesc.Count = 1;
	//textureDesc.SampleDesc.Quality = 0;
	//textureDesc.Usage = D3D11_USAGE_IMMUTABLE;
	//textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	//textureDesc.CPUAccessFlags = 0;
	//textureDesc.MiscFlags = 0;

	//D3D11_SUBRESOURCE_DATA sd[AustinHead_numlevels] = {};
	//for (int i = 0; i < AustinHead_numlevels; ++i)
	//{
	//	sd[i].pSysMem = &AustinHead_pixels[AustinHead_leveloffsets[i]];
	//	sd[i].SysMemPitch = (AustinHead_width >> i) * sizeof(unsigned int);
	//}

	//HRESULT hr = GetDevice(gfx)->CreateTexture2D(
	//	&textureDesc, sd, &pTexture);

	//D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	//srvDesc.Format = textureDesc.Format;
	//srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	//srvDesc.Texture2D.MostDetailedMip = 0;
	//srvDesc.Texture2D.MipLevels = 1;

	//GetDevice(gfx)->CreateShaderResourceView(
	//	pTexture, &srvDesc, &pTextureView
	//);
	// DDS Loader
	CreateDDSTextureFromFile(GetDevice(gfx), filename, 
		(ID3D11Resource**)&pEnvironmentTexture, &pEnvironmentTextureView);

}

void Texture::SetTexture(Graphics& gfx)
{
	GetContext(gfx)->PSSetShaderResources(0, 1, &pEnvironmentTextureView);
}

ID3D11DeviceContext* Texture::GetContext(Graphics& gfx)
{
	return gfx.pContext;
}

ID3D11Device* Texture::GetDevice(Graphics& gfx)
{
	return gfx.pDevice;
}