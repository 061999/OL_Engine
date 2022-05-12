#include "core.h"
#include "Image.h"

Image::Image(const char * path)
{
	data = stbi_load( path , &width , &height , &channel , 4 );
}

Image::~Image()
{
	stbi_image_free( data );
}

UINT Image::GetWidth()
{
	return width;
}

UINT Image::GetHeight()
{
	return height;
}

UINT Image::GetLineWidth()
{
	return 4 * width * sizeof( unsigned char );
}

unsigned char * Image::GetData()
{
	return data;
}

DXGI_FORMAT Image::Format()
{
	return DXGI_FORMAT_R8G8B8A8_UNORM;
}
