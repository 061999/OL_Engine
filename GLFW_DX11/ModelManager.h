#pragma once
#include "Model.h"
#include <mutex>
class ModelManager
{
public:
	ModelManager();
	void LoadModel( const char * path );
	void DropCallBack( vector<char[128]> & paths );
	void Render();
	std::function<void()> Fn_RenderUI;
private:
	void RenderUI();
	vector<Model *> mods;
	vector<const char *> modNames;
	std::mutex mod_Lock;
};

