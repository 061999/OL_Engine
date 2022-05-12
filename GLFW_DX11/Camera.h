#pragma once
#include "ConstantBuffer.h"
class Camera
{
public:
	Camera( int width , int height );
	void Update( float dt );
	void MouseCallBack( float x , float y );
	void ResizeCallBack( int width , int height );
private:
	dx::XMMATRIX perspective;
	dx::XMVECTOR dirction;
	dx::XMVECTOR position;
	dx::XMVECTOR front;
	dx::XMVECTOR right;
	dx::XMVECTOR up;
	unique_ptr<ConstantBuffer<dx::XMMATRIX>> transMat;
};

