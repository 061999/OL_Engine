#pragma once
#include "VertexArray.h"
#include "Shader.h"
#include "Sampler.h"
#include "ConstantBuffer.h"
#include "Material.h"
class Model
{
private:
	class Mesh
	{
	public:
		Mesh( aiMesh * mesh );
		void Draw();
	private:
		unique_ptr<VertexArray> vertex;
	};
public:
	Model( const char * path );
	void RenderUI();
	void Draw();
private:
	friend class ModelManager;
	float x , y , z , yaw , row , pitch , scaling;
	string ImGui_Name;

	static unique_ptr<Shader> shader;
	static unique_ptr<Sampler> sampler;
	unique_ptr<ConstantBuffer<dx::XMMATRIX>> transMat;
	vector<Mesh> meshes;
	unique_ptr<Material> material;
};

