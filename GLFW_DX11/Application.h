#pragma once
#include "Window.h"
#include "Graphics.h"

#include "Camera.h"
#include "ImGuiLayer.h"
#include "ModelManager.h"

class Application
{
public:
	Application();
	void GO();
private:
	unique_ptr<Window> win;
	unique_ptr<Graphics> gfx;
	unique_ptr<Camera> camera;
	unique_ptr<ModelManager> modeler;
	unique_ptr<ImGuiLayer> imguiLayer;
	Timer time;
};

