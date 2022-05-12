#pragma once
#include "Bindable.h"
class VertexArray :public Bindable
{
public:
	// Í¨¹ý Bindable ¼Ì³Ð
	virtual void Bind() override;
public:
	template<typename T>
	VertexArray( vector<T> & vertices , vector<unsigned int> & indices )
	{
		D3D11_BUFFER_DESC vbd = {};
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbd.Usage = D3D11_USAGE_DEFAULT;
		vbd.CPUAccessFlags = 0u;
		vbd.MiscFlags = 0u;
		vbd.ByteWidth = (UINT)(sizeof( T ) * vertices.size());
		vbd.StructureByteStride = (UINT)sizeof( T );
		D3D11_SUBRESOURCE_DATA vsd = {};
		vsd.pSysMem = vertices.data();
		device->CreateBuffer( &vbd , &vsd , vertexBuffer.GetAddressOf() );

		D3D11_BUFFER_DESC ibd = {};
		ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibd.Usage = D3D11_USAGE_DEFAULT;
		ibd.CPUAccessFlags = 0u;
		ibd.MiscFlags = 0u;
		ibd.ByteWidth = indices.size() * sizeof( unsigned int );
		ibd.StructureByteStride = sizeof( unsigned int );
		D3D11_SUBRESOURCE_DATA isd = {};
		isd.pSysMem = indices.data();
		device->CreateBuffer( &ibd , &isd , indexBuffer.GetAddressOf() );

		stride = (UINT)sizeof( T );
		indexCount = (UINT)indices.size();
	}
	void Draw();
private:
	UINT indexCount = 0u;
	UINT stride = 0u;
	UINT offset = 0u;
	ComPtr<ID3D11Buffer> vertexBuffer;
	ComPtr<ID3D11Buffer> indexBuffer;
};

