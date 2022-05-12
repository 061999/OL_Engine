#pragma once
#include <string>
#include <vector>
struct MODEL_DESC
{
	float x , y , z , yaw , row , pitch , scaling;
	std::string name;
	std::string sourcePath;
	std::vector<std::string> texturePaths;
	std::vector<int> texIDbyMesh;
};
void ConfigGetModelDescByPath( const char * path , MODEL_DESC & desc );