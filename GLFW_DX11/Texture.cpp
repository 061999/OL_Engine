#include "core.h"
#include "Texture.h"
#include "Image.h"

struct TEXTURE_DESC :public D3D11_TEXTURE2D_DESC
{
	TEXTURE_DESC( Image & img )
	{
		Width = img.GetWidth();
		Height = img.GetHeight();
		MipLevels = 1;
		ArraySize = 1;
		Format = img.Format();
		SampleDesc.Count = 1;
		SampleDesc.Quality = 0;
		Usage = D3D11_USAGE_DEFAULT;
		BindFlags = D3D11_BIND_SHADER_RESOURCE;
		CPUAccessFlags = 0;
		MiscFlags = 0;
	}
};

struct TEXTURE_VIEW_DESC :public D3D11_SHADER_RESOURCE_VIEW_DESC
{
	TEXTURE_VIEW_DESC( Image & img )
	{
		Format = img.Format();
		ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		Texture2D.MostDetailedMip = 0;
		Texture2D.MipLevels = 1;
	}
};
void Texture::Bind()
{
	context->PSSetShaderResources( startSlot , 1u , texview.GetAddressOf() );
}

Texture::Texture( const char * path , UINT slot )
{ 
	startSlot = slot;
	Image img( path );
	TEXTURE_DESC tex_desc( img );
	D3D11_SUBRESOURCE_DATA data = {};
	data.pSysMem = img.GetData();
	data.SysMemPitch = img.GetLineWidth();

	ComPtr<ID3D11Texture2D> pTexture;
	device->CreateTexture2D( &tex_desc , &data , pTexture.GetAddressOf() );

	TEXTURE_VIEW_DESC tex_view_desc( img );
	device->CreateShaderResourceView( pTexture.Get() , &tex_view_desc , texview.GetAddressOf() );

	
}
