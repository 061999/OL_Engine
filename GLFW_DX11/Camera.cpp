#include "core.h"
#include "Camera.h"

Camera::Camera( int width , int height )
{
	transMat = make_unique<ConstantBuffer<dx::XMMATRIX>>();
	transMat->Bind_VS();
	dirction = dx::XMVectorSet( 0.0f , 0.0f , 0.0f , 0.0f );
	position = dx::XMVectorSet( 0.0f , 0.0f , -13.0f , 0.0f );
	front = dx::XMVectorSet( 0.0f , 0.0f , 1.0f , 0.0f );
	right = dx::XMVectorSet( -1.0f , 0.0f , 0.0f , 0.0f );
	up = dx::XMVectorSet( 0.0f , 1.0f , 0.0f , 0.0f );
	perspective = dx::XMMatrixPerspectiveFovLH( 0.78f , (float)width / (float)height , 0.01f , 1000.0f );
}

void Camera::Update( float dt )
{
    dt *= 3.0f;
    if( Keyborad::isKeyDown( 'W' ) )
    {
        position = dx::XMVectorAdd( position , dx::XMVectorScale( front , dt ) );
    }
    if( Keyborad::isKeyDown( 'A' ) )
    {
        position = dx::XMVectorAdd( position , dx::XMVectorScale( right , dt ) );
    }
    if( Keyborad::isKeyDown( 'S' ) )
    {
        position = dx::XMVectorSubtract( position , dx::XMVectorScale( front , dt ) );
    }
    if( Keyborad::isKeyDown( 'D' ) )
    {
        position = dx::XMVectorSubtract( position , dx::XMVectorScale( right , dt ) );
    }
    if( Keyborad::isKeyDown( 'R' ) )
    {
        position = dx::XMVectorAdd( position , dx::XMVectorScale( up , dt ) );
    }
    if( Keyborad::isKeyDown( 'F' ) )
    {
        position = dx::XMVectorSubtract( position , dx::XMVectorScale( up , dt ) );
    }
	transMat->Update( dx::XMMatrixTranspose( dx::XMMatrixMultiply( dx::XMMatrixLookToLH( position , front , up ) , perspective ) ) );
}

void Camera::MouseCallBack( float x , float y )
{
	dirction.m128_f32[1] += dx::XMConvertToRadians( x ) * 0.04f;
	dirction.m128_f32[0] += dx::XMConvertToRadians( y ) * 0.04f;
	front = dx::XMVector3Transform( dx::XMVectorSet( 0.0f , 0.0f , 1.0f , 0.0f ) , dx::XMMatrixRotationRollPitchYawFromVector( dirction ) );
	right = dx::XMVector3Cross( front , up );
}

void Camera::ResizeCallBack( int width , int height )
{
	perspective = dx::XMMatrixPerspectiveFovLH( 0.78f , (float)width / (float)height , 0.01f , 1000.0f );
}
