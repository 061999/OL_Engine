#include "core.h"
#include "Bindable.h"

ID3D11Device * Bindable::device = nullptr;
ID3D11DeviceContext * Bindable::context = nullptr;

void Bindable::Init( ID3D11Device * d , ID3D11DeviceContext * c )
{
	device = d;
	context = c;
}
