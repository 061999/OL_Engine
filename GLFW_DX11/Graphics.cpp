#include "core.h"
#include "Graphics.h"

struct SWAP_CHAIN_DESC_EXTENSION : public DXGI_SWAP_CHAIN_DESC
{
    SWAP_CHAIN_DESC_EXTENSION( HWND win , int width , int height )
    {
        DXGI_MODE_DESC mode_desc = {};

        mode_desc.Width = width;
        mode_desc.Height = height;
        mode_desc.RefreshRate = { 0u,0u };
        mode_desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        mode_desc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        mode_desc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

        BufferDesc = mode_desc;
        SampleDesc = { 4u,0u };
        BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        BufferCount = 1u;
        OutputWindow = win;
        Windowed = TRUE;
        SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
        Flags = 0u;
    }
};

struct VIEW_PORT_EXTENSION : public D3D11_VIEWPORT
{
    VIEW_PORT_EXTENSION( float width , float height )
    {
        TopLeftX = 0.0f;
        TopLeftY = 0.0f;
        Width = width;
        Height = height;
        MinDepth = 0.0f;
        MaxDepth = 1.0f;
    }
};

struct DEPTH_STENCIL_VIEW_DESC :public D3D11_TEXTURE2D_DESC
{
    DEPTH_STENCIL_VIEW_DESC( UINT width , UINT height )
    {
        Width = width;
        Height = height;
        MipLevels = 1u;
        ArraySize = 1u;
        Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        SampleDesc = { 4u,0u };
        Usage = D3D11_USAGE_DEFAULT;
        BindFlags = D3D11_BIND_DEPTH_STENCIL;
        CPUAccessFlags = 0u;
        MiscFlags = 0u;
    }
};

Graphics::Graphics( HWND win , int width , int height )
{
    //Create SwapChain and Device and Context
    
    
    SWAP_CHAIN_DESC_EXTENSION swapchain_desc( win , width , height );
    D3D11CreateDeviceAndSwapChain( nullptr,
                                   D3D_DRIVER_TYPE_HARDWARE ,
                                   nullptr ,
                                   0u ,
                                   nullptr ,
                                   0u ,
                                   D3D11_SDK_VERSION ,
                                   &swapchain_desc ,
                                   swapchain.GetAddressOf() ,
                                   device.GetAddressOf() ,
                                   nullptr ,
                                   context.GetAddressOf()
    );
    context->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

    Resize( width , height );
}

ID3D11Device * Graphics::GetDevice()
{
    return device.Get();
}

ID3D11DeviceContext * Graphics::GetContext()
{
    return context.Get();
}

void Graphics::Resize( int width , int height )
{
    swapchain->ResizeBuffers( 1u , width , height , DXGI_FORMAT_R8G8B8A8_UNORM , 0u );
    RTV.Reset();
    DSV.Reset();
    //Create Render Target View
    ComPtr<ID3D11Resource> buffer;
    swapchain->GetBuffer( 0u , IID_PPV_ARGS( buffer.GetAddressOf() ) );
    device->CreateRenderTargetView( buffer.Get() , nullptr , RTV.GetAddressOf() );

    //Create Depth Stencil View
    DEPTH_STENCIL_VIEW_DESC depth_desc( width , height );
    ComPtr<ID3D11Texture2D> depthBuffer;
    device->CreateTexture2D( &depth_desc , nullptr , depthBuffer.GetAddressOf() );
    device->CreateDepthStencilView( depthBuffer.Get() , nullptr , DSV.GetAddressOf() );


    context->OMSetRenderTargets( 1u , RTV.GetAddressOf() , DSV.Get() );
    VIEW_PORT_EXTENSION viewport( (float)width , (float)height );
    context->RSSetViewports( 1u , &viewport );

    D3D11_DEPTH_STENCIL_DESC dsd = {};
}

void Graphics::Swap()
{
    swapchain->Present( 0u , 0u );
}

void Graphics::Clear()
{
    context->ClearRenderTargetView( RTV.Get() , dx::Colors::Aqua );
    context->ClearDepthStencilView( DSV.Get() , D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL , 1.0f , 0u );
}

void Graphics::SetRenderTarget()
{
    context->OMSetRenderTargets( 1u , RTV.GetAddressOf() , DSV.Get() );
}
