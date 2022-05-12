#pragma once
#include "Bindable.h"
class Sampler : public Bindable
{
public:
	// ͨ�� Bindable �̳�
	virtual void Bind() override;
public:
	Sampler( UINT slot = 0u );
private:
	ComPtr<ID3D11SamplerState> samplerState;
	UINT samplerSlot;
};

