#include "core.h"
#include "Material.h"

Material::Material( MODEL_DESC & desc )
{
	for( size_t i = 0; i < desc.texturePaths.size(); i++ )
	{
		textures.emplace_back( desc.texturePaths[i].c_str() );
	}
	ids = desc.texIDbyMesh;
}

void Material::BindByMeshId( int id )
{
	textures[ids[id]].Bind();
}
