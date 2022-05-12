#include "core.h"
#include "Sampler.h"

Sampler::Sampler( UINT slot )
{
	samplerSlot = slot;
	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.Filter = D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	device->CreateSamplerState( &samplerDesc , samplerState.GetAddressOf() );
}

void Sampler::Bind()
{
	context->PSSetSamplers( samplerSlot , 1u , samplerState.GetAddressOf() );
}
