#include <stdio.h>

#include "Core/WindowsApp.h"
//#include "SampleState.h"

INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
	framework12::WindowsApp app;

	if (app.Init(L"Sample Window"))
	{
		app.Run();
	}

	return 0;
}