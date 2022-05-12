#include "core.h"
#include "Application.h"


Application::Application()
{

	win = make_unique<Window>( 1200 , 800 , L"Hello" );
	gfx = make_unique<Graphics>( win->GetHWND() , win->GetWidth() , win->GetHeight() );
	Bindable::Init( gfx->GetDevice() , gfx->GetContext() );  
	
	imguiLayer = make_unique<ImGuiLayer>( win->GetHWND() , gfx->GetDevice() , gfx->GetContext() );
	
	camera = make_unique<Camera>( win->GetWidth() , win->GetHeight() );
	win->PushCallBackMouseDelta( std::bind( &Camera::MouseCallBack , camera.get() , std::placeholders::_1 , std::placeholders::_2 ) );
	
	
	modeler = make_unique<ModelManager>();
	win->PushCallBackDropFile( std::bind( &ModelManager::DropCallBack , modeler.get() , std::placeholders::_1 ) );
	vector<char[128]>path(2);
	memcpy( path[0] , "json/ng.json" , 13 );
	memcpy( path[1] , "json/lisha.json" , 16 );

	modeler->DropCallBack( path );
}

void Application::GO()
{
	while( Window::m_WindowState )
	{
		Window::EventPoll();
		camera->Update( time.Delta() );
		gfx->Clear();

		//DOFrame
		//-DOFrame

		modeler->Render();
		imguiLayer->Begin();
		modeler->Fn_RenderUI();
		imguiLayer->DrawGraphics();
		imguiLayer->End();

		gfx->Swap();
	}
}



/*


struct Vertex
	{
		float x , y , z;
		float r , g;
	};

	vector<Vertex> vertices = {

		{ -0.5f, 0.5f,0.0f,0.0f,0.0f },
		{ -0.5f,-0.5f,0.0f,0.0f,1.0f },
		{  0.5f,-0.5f,0.0f,1.0f,1.0f },
		{  0.5f, 0.5f,0.0f,1.0f,0.0f },

		
		{ -1.0f,-1.0f,-1.0f, 1.0f,0.0f,0.0f},
		{ 1.0f,-1.0f,-1.0f , 0.0f,1.0f,0.0f},
		{ -1.0f,1.0f,-1.0f , 0.0f,0.0f,1.0f},
		{ 1.0f,1.0f,-1.0f , 0.2f,0.4f,0.6f},
		{ -1.0f,-1.0f,1.0f ,0.3f,0.5f,0.7f},
		{ 1.0f,-1.0f,1.0f ,0.9f,0.5f,0.3f},
		{ -1.0f,1.0f,1.0f ,0.5f,1.0f,0.6f},
		{ 1.0f,1.0f,1.0f ,0.3f,0.4f,0.5f},
		
	};
	vector<unsigned int> indices = {
		0,2,1,
		0,3,2,
		
		0,2,1, 2,3,1,
		1,3,5, 3,7,5,
		2,6,3, 3,6,7,
		4,5,7, 4,7,6,
		0,4,2, 2,4,6,
		0,1,4, 1,5,4
		
	};
*/