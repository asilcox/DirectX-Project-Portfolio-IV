#include "Application.h"

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hprevInstance,
	LPSTR	  lpCmdLine,
	int		  nCmdShow)
{
	return Application{}.Start();
}