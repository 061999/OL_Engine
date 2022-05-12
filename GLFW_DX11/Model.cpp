#include "core.h"
#include "Model.h"

unique_ptr<Shader> Model::shader;
unique_ptr<Sampler> Model::sampler;

Model::Mesh::Mesh( aiMesh * mesh )
{
	struct Vertex
	{
		aiVector3D pos;
		aiVector3D texcoord;
	};
	vector<Vertex> vertices;
	vertices.reserve( mesh->mNumVertices );
	for( size_t i = 0; i < mesh->mNumVertices; i++ )
	{
		vertices.push_back( { mesh->mVertices[i],mesh->mTextureCoords[0][i] } );
	}
	vector<unsigned int> indices;
	indices.reserve( mesh->mNumFaces * 3 );
	for( size_t i = 0; i < mesh->mNumFaces; i++ )
	{
		for( size_t j = 0; j < mesh->mFaces[i].mNumIndices; j++ )
		{
			indices.push_back( mesh->mFaces[i].mIndices[j] );
		}
	}
	vertex = make_unique<VertexArray>( vertices , indices );
}

void Model::Mesh::Draw()
{ 
	vertex->Bind();
	vertex->Draw();
}

Model::Model( const char * path )
{
	MODEL_DESC desc;
	ConfigGetModelDescByPath( path , desc );
	Assimp::Importer imp;
	auto pScene = imp.ReadFile( desc.sourcePath.c_str() ,
								aiProcess_Triangulate |
								aiProcess_JoinIdenticalVertices |
								aiProcess_ConvertToLeftHanded );
	for( size_t i = 0; i < pScene->mNumMeshes; i++ )
	{
		meshes.emplace_back( pScene->mMeshes[i] );
	}
	if( shader.get() == nullptr )
	{
		InputLayout layout;
		layout.Push_float_3( "POSITION" );
		layout.Push_float_3( "TEXCOORD" );
		shader = make_unique<Shader>( L"cso/VS.cso" , L"cso/PS.cso" , layout );
	}
	if( sampler.get() == nullptr )
	{
		sampler = make_unique<Sampler>();
	}
	transMat = make_unique<ConstantBuffer<dx::XMMATRIX>>( 1u );
	material = make_unique<Material>( desc );
	ImGui_Name = desc.name;
	x = desc.x;
	y = desc.y;
	z = desc.z;
	yaw = desc.yaw;
	row = desc.row;
	pitch = desc.pitch;
	scaling = desc.scaling;
}

void Model::RenderUI()
{
	ImGui::DragFloat( "X" , &x , 0.01f );
	ImGui::DragFloat( "Y" , &y , 0.01f );
	ImGui::DragFloat( "Z" , &z , 0.01f );
	ImGui::SliderAngle( "Yaw" , &yaw );
	ImGui::SliderAngle( "Row" , &row );
	ImGui::SliderAngle( "Pitch" , &pitch );
	ImGui::DragFloat( "Scaling" , &scaling , 0.01f , 0.01f , 3.0f );
}

void Model::Draw()
{
	using namespace dx;
	shader->Bind();
	sampler->Bind();
	transMat->Update(
		dx::XMMatrixTranspose(
		dx::XMMatrixRotationRollPitchYaw( pitch , yaw , row )*
		dx::XMMatrixScaling( scaling , scaling , scaling ) * 
		dx::XMMatrixTranslation( x , y , z ) 
	)
	);
	transMat->Bind_VS();
	for( int i = 0; i < meshes.size(); i++ )
	{
		material->BindByMeshId( i );
		meshes[i].Draw();
	}
}
