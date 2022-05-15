#include "core.h"
#include "ImGuiLayer.h"

ImGuiLayer::ImGuiLayer( HWND win , ID3D11Device * device , ID3D11DeviceContext * context )
{
   // IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO & io = ImGui::GetIO();
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui_ImplWin32_Init( win );
    ImGui_ImplDX11_Init( device , context );
}

void ImGuiLayer::Begin()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

}

void ImGuiLayer::Render()
{
    ImGui::Render();
}

void ImGuiLayer::DrawGraphics()
{
    ImGui::Begin( "Graphics" );
    ImGui::Text( "FPS : %.2f" , ImGui::GetIO().Framerate );
    ImGui::End();
}

void ImGuiLayer::End()
{
    ImGui_ImplDX11_RenderDrawData( ImGui::GetDrawData() );

   // ImGui::UpdatePlatformWindows();
    //ImGui::RenderPlatformWindowsDefault();
}
