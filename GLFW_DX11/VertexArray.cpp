#include "core.h"
#include "VertexArray.h"

void VertexArray::Bind()
{
	context->IASetVertexBuffers( 0u , 1u , vertexBuffer.GetAddressOf() , &stride , &offset );
	context->IASetIndexBuffer( indexBuffer.Get() , DXGI_FORMAT_R32_UINT , 0u );
}

void VertexArray::Draw()
{
	context->DrawIndexed( indexCount , 0u , 0 );
}
