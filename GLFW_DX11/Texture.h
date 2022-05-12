#pragma once
#include "Bindable.h"
class Texture: public Bindable
{
public:
	// Í¨¹ý Bindable ¼Ì³Ð
	virtual void Bind() override;
public:
	Texture( const char * path , UINT slot = 0u );
private:
	UINT startSlot;
	ComPtr<ID3D11ShaderResourceView> texview;
};

