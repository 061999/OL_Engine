#include "Keyborad.h"

bool Keyborad::KEY_STATE[256] = { false };

void Keyborad::OnPress( const int & code )
{
    KEY_STATE[code] = true;
}

void Keyborad::OnRelease( const int & code )
{
    KEY_STATE[code] = false;
}

bool Keyborad::isKeyDown( const unsigned char & code )
{
    return KEY_STATE[code];
}
