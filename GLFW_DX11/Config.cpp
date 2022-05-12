#include "Config.h"
#include <fstream>
#include <iostream>

#include "json.hpp"
#include <spdlog\spdlog.h>

void ConfigGetModelDescByPath( const char * path , MODEL_DESC & desc )
{
	std::ifstream jsonfile( path );
	if( jsonfile.is_open() )
	{
		spdlog::info( "open file success" );
	}
	else
	{
		spdlog::critical( "open file failed" );
	}

	nlohmann::json j;

	jsonfile >> j;

	jsonfile.close();

	desc.name = j.find( "name" )->get<std::string>();
	desc.sourcePath = j.find( "path" )->get<std::string>();
	desc.texturePaths = j.find( "diffuse" )->get<std::vector<std::string>>();
	desc.texIDbyMesh = j.find( "id" )->get<std::vector<int>>();
	desc.x = j.find( "x" )->get<float>();
	desc.y = j.find( "y" )->get<float>();
	desc.z = j.find( "z" )->get<float>();
	desc.yaw = j.find( "yaw" )->get<float>();
	desc.row = j.find( "row" )->get<float>();
	desc.pitch = j.find( "pitch" )->get<float>();
	desc.scaling = j.find( "scaling" )->get<float>();
}
