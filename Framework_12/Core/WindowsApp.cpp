#include "WindowsApp.h"

#define WindowStyle WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX

namespace framework12
{
	LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	WindowsApp::WindowsApp()
		: m_instanceHandle(nullptr)
		, m_windowHandle(nullptr)
		, m_wndClassEx()
	{
	}
	WindowsApp::~WindowsApp()
	{
		FreeDevice();
	}

	bool WindowsApp::Init(const wchar_t *windowName, int width, int height)
	{
		m_wndClassEx.cbSize = sizeof(WNDCLASSEX);
		m_wndClassEx.style = CS_CLASSDC;
		m_wndClassEx.lpfnWndProc = MsgProc;
		m_wndClassEx.cbClsExtra = 0L;
		m_wndClassEx.cbWndExtra = 0L;
		m_wndClassEx.hInstance = m_instanceHandle;
		m_wndClassEx.hIcon = nullptr;
		m_wndClassEx.hCursor = LoadCursor(nullptr, IDC_ARROW);
		m_wndClassEx.hbrBackground = nullptr;
		m_wndClassEx.lpszMenuName = nullptr;
		m_wndClassEx.lpszClassName = L"framework_12";
		m_wndClassEx.hIconSm = nullptr;
		RegisterClassExW(&m_wndClassEx);

		int screenX = GetSystemMetrics(SM_CXSCREEN);
		int screenY = GetSystemMetrics(SM_CYSCREEN);

		RECT windowRect;
		ZeroMemory(&windowRect, sizeof(windowRect));
		windowRect.left = (screenX - width) / 2;
		windowRect.top = (screenY - height) / 2;
		windowRect.right = windowRect.left + width;
		windowRect.bottom = windowRect.top + height;
		AdjustWindowRectEx(&windowRect, WindowStyle, 0, 0);

		m_windowHandle = CreateWindowExW(
			0L, m_wndClassEx.lpszClassName, windowName,
			WindowStyle,
			windowRect.left, windowRect.top, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top,
			nullptr, nullptr, m_wndClassEx.hInstance, nullptr
		);

		m_width = width;
		m_height = height;

		if (!AllocDevice())
			return false;

		return true;
	}

	void WindowsApp::Run()
	{
		ShowWindow(m_windowHandle, SW_SHOWDEFAULT);
		UpdateWindow(m_windowHandle);

		{
			MSG msg;
			ZeroMemory(&msg, sizeof(msg));

			while (msg.message != WM_QUIT)
			{
				while (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}

			UnregisterClassW(m_wndClassEx.lpszClassName, m_wndClassEx.hInstance);
			FreeDevice();
		}
	}

	bool WindowsApp::AllocDevice()
	{
		return true;
	}

	void WindowsApp::FreeDevice()
	{
	}

	LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}