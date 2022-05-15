#pragma once
class ImGuiLayer
{
public:
	ImGuiLayer( HWND win , ID3D11Device * device , ID3D11DeviceContext * context );
	void Begin();
	void Render();
	void DrawGraphics();
	void End();
private:
};

