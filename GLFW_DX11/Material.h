#pragma once
#include "Texture.h"
class Material
{
public:
	Material( MODEL_DESC & desc );
	void BindByMeshId( int id );
private:
	vector<Texture> textures;
	vector<int> ids;
};

