#include "core.h"
#include "ModelManager.h"
#include <thread>

ModelManager::ModelManager()
{
	Fn_RenderUI = []() { };
}

void ModelManager::LoadModel( const char * path )
{
	Model * temp = new Model( path );
	mod_Lock.lock();
	if( mods.empty() )
	{
		Fn_RenderUI = std::bind( &ModelManager::RenderUI , this );
	}
	mods.push_back( temp );
	modNames.push_back( temp->ImGui_Name.c_str() );
	mod_Lock.unlock();
}

void ModelManager::DropCallBack( vector<char[128]> & paths )
{
	vector<std::thread>threadLoader;
	for( size_t i = 0; i < paths.size(); i++ )
	{
		threadLoader.emplace_back( std::bind( &ModelManager::LoadModel , this , paths[i] ) );
	}
	for( size_t i = 0; i < threadLoader.size(); i++ )
	{
		threadLoader[i].join();
	}
}

void ModelManager::Render()
{
	mod_Lock.lock();
	for( auto & m : mods )
	{
		m->Draw();
	}
	mod_Lock.unlock();
}

void ModelManager::RenderUI()
{
	mod_Lock.lock();
	ImGui::Begin( "Model_Manager" );
	static int item_current = 0;
	ImGui::Combo( "Current Model" , &item_current , modNames.data() , (int)modNames.size() );
	mods[item_current]->RenderUI();
	ImGui::End();
	mod_Lock.unlock();
}
