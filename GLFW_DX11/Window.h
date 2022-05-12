#pragma once
class Window
{
private:
	class WindowClass
	{
	public:
		WindowClass();
		~WindowClass();

		LPCWSTR GetName();
		UINT GetStyle();
		HINSTANCE GetInstance();
	private:
		WNDCLASSEX wc;
		HINSTANCE hInstance;
		std::wstring ClassName{ L"Hello Window Class" };
	};
	static std::unique_ptr<WindowClass> m_WindowClass;
	static bool m_CursorState;
	HWND hwnd;
	int width;
	int height;
	char mouseRawData[1024];
	unsigned int mouseRawDataSize;
	vector<std::function<void( WPARAM )>> Fn_KeyDown;
	vector<std::function<void( float , float )>> Fn_MouseDelta;
	vector<std::function<void( vector<char[128]> & )>> Fn_DropFile;
	vector<std::function<void( int , int )>> Fn_Resize;
private:
	void HandMsg( HWND hWnd , UINT msg , WPARAM wParam , LPARAM lParam );
	friend LRESULT ProcMessage( HWND hWnd , UINT msg , WPARAM wParam , LPARAM lParam );
public:
	static bool m_WindowState;
public:
	Window( int width , int height , const wchar_t * title = L"Hello" );
	static void EventPoll();
	HWND GetHWND();
	int GetWidth() const;
	int GetHeight() const;
	void EnableCursor() const;
	void DisableCursor() const;
	void PushCallBackKeyDown( const std::function<void( WPARAM )> & temp );
	void PushCallBackMouseDelta( const std::function<void( float , float )> & temp );
	void PushCallBackDropFile( const std::function<void( vector<char[128]> & )> & temp );
	void PushCallBackResize( const std::function<void( int , int )> & temp );
};

