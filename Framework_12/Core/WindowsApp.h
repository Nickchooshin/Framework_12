#ifndef _WIN_SYSTEM_H_
#define _WIN_SYSTEM_H_

#include <Windows.h>

namespace framework12
{
	class WindowsApp
	{
	private :
		HINSTANCE m_instanceHandle;
		HWND m_windowHandle;
		WNDCLASSEXW m_wndClassEx;
		int m_width, m_height;

	public :
		WindowsApp();
		~WindowsApp();

		bool Init(const wchar_t *windowName, int width = 640, int height = 480);
		
		void Run();
	private:
		bool AllocDevice();
		void FreeDevice();
	};
}

#endif