#pragma once
class Image
{
public:
	Image(const char * path);
	~Image();
	UINT GetWidth();
	UINT GetHeight();
	UINT GetLineWidth();
	unsigned char * GetData();
	DXGI_FORMAT Format();
private:
	int width , height , channel;
	unsigned char * data;

};

