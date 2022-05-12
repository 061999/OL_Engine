#pragma once
class Graphics
{ 
public:
	Graphics( HWND win , int width , int height );
	
	ID3D11Device * GetDevice();
	ID3D11DeviceContext * GetContext();
	void Resize( int width , int height );
	void Swap();
	void Clear();
private:
	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> context;
	ComPtr<IDXGISwapChain> swapchain;

	ComPtr<ID3D11RenderTargetView> RTV;
	ComPtr<ID3D11DepthStencilView> DSV;
	
};

