#pragma once
#include "Bindable.h"
template<typename T>
class ConstantBuffer :public Bindable
{ 

public:
	virtual void Bind() override
	{ }

public:
	ConstantBuffer( UINT slot = 0 )
	{
		Slot = slot;
		D3D11_BUFFER_DESC cbd;
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.MiscFlags = 0u;
		cbd.ByteWidth = sizeof( T );
		cbd.StructureByteStride = 0u;

		device->CreateBuffer( &cbd , nullptr , constantBuffer.GetAddressOf() );
	}
	void Update( const T & data )
	{
		static D3D11_MAPPED_SUBRESOURCE msr;
		context->Map( constantBuffer.Get() , 0u , D3D11_MAP_WRITE_DISCARD , 0u , &msr );
		memcpy( msr.pData , &data , sizeof( T ) );
		context->Unmap( constantBuffer.Get() , 0u );
	}

	void Bind_VS()
	{
		context->VSSetConstantBuffers( Slot , 1u , constantBuffer.GetAddressOf() );
	}

	void Bind_PS()
	{
		context->PSSetConstantBuffers( Slot , 1u , constantBuffer.GetAddressOf() );
	}
private:
	UINT Slot;
	ComPtr<ID3D11Buffer> constantBuffer;

	// Í¨¹ý Bindable ¼Ì³Ð
	
};

