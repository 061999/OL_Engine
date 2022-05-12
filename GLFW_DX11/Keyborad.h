#pragma once
class Keyborad
{
public:
	static void OnPress(const int & code );
	static void OnRelease(const int & code );
	static bool isKeyDown( const unsigned char & code );
private:
	static bool KEY_STATE[256];
};

