#include "cGame.h"
using namespace FrameworkX;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{	

	// Make sure to set this. Some classes, like the exception handler and custom cursors
	// will need to use it.
	gHInstance = hInstance;

	// Create and initialize our game application.
	cGame* anApp = new cGame();
	anApp->Init();
	anApp->Start();
	delete anApp;

	return 0;
}