#pragma once
class Bindable
{ 
public:
	virtual void Bind() = 0;
	static void Init( ID3D11Device * d , ID3D11DeviceContext * c );
protected:
	static ID3D11Device * device;
	static ID3D11DeviceContext * context;
};

