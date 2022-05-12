#pragma once
#include <array>
#include "Bindable.h"

class InputLayout
{
public:
	void Push_float_1(LPCSTR name);
	void Push_float_2(LPCSTR name);
	void Push_float_3(LPCSTR name);
	void Push_float_4(LPCSTR name);
	
	void Push_int_1(LPCSTR name);
	void Push_int_2(LPCSTR name);
	void Push_int_3(LPCSTR name);
	void Push_int_4(LPCSTR name);
private:
	UINT offset = 0u;
	friend class Shader;
	vector<D3D11_INPUT_ELEMENT_DESC> layout;
};


class Shader :public Bindable
{
public:
	// Í¨¹ý Bindable ¼Ì³Ð
	virtual void Bind() override;
public:
	Shader( const wchar_t * vs_path , const wchar_t * ps_path , InputLayout & layout );
private:
	ComPtr<ID3D11VertexShader> vertexShader;
	ComPtr<ID3D11PixelShader> pixelShader;
	ComPtr<ID3D11InputLayout> inputLayout;
};

