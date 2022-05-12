#include "core.h"
#include "Shader.h"

void Shader::Bind()
{ 
	context->VSSetShader( vertexShader.Get() , nullptr , 0u );
	context->PSSetShader( pixelShader.Get() , nullptr , 0u );
	context->IASetInputLayout( inputLayout.Get() );
}

Shader::Shader( const wchar_t * vs_path , const wchar_t * ps_path , InputLayout & layout )
{
	ComPtr<ID3DBlob> b;
	D3DReadFileToBlob( vs_path , b.GetAddressOf() );
	device->CreateVertexShader( b->GetBufferPointer() , b->GetBufferSize() , nullptr , vertexShader.GetAddressOf() );

	device->CreateInputLayout( layout.layout.data() , (UINT)layout.layout.size() , b->GetBufferPointer() , b->GetBufferSize() , inputLayout.GetAddressOf() );

	ComPtr<ID3DBlob> b1;
	D3DReadFileToBlob( ps_path , b1.GetAddressOf() );
	device->CreatePixelShader( b1->GetBufferPointer() , (UINT)b1->GetBufferSize() , nullptr , pixelShader.GetAddressOf() );

}

void InputLayout::Push_float_1( LPCSTR name )
{ 
	layout.push_back( { name,0,DXGI_FORMAT_R32_FLOAT,0,offset,D3D11_INPUT_PER_VERTEX_DATA,0 } );
	offset += sizeof( float );
}

void InputLayout::Push_float_2( LPCSTR name )
{
	layout.push_back( { name,0,DXGI_FORMAT_R32G32_FLOAT,0,offset,D3D11_INPUT_PER_VERTEX_DATA,0 } );
	offset += sizeof( float ) * 2;
}

void InputLayout::Push_float_3( LPCSTR name )
{
	layout.push_back( { name,0,DXGI_FORMAT_R32G32B32_FLOAT,0,offset,D3D11_INPUT_PER_VERTEX_DATA,0 } );
	offset += sizeof( float ) * 3;
}

void InputLayout::Push_float_4( LPCSTR name )
{
	layout.push_back( { name,0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,offset,D3D11_INPUT_PER_VERTEX_DATA,0 } );
	offset += sizeof( float ) * 4;
}

void InputLayout::Push_int_1( LPCSTR name )
{ }

void InputLayout::Push_int_2( LPCSTR name )
{ }

void InputLayout::Push_int_3( LPCSTR name )
{ }

void InputLayout::Push_int_4( LPCSTR name )
{ }
