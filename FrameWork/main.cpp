#include <cstdlib>
#include <crtdbg.h>
#include "Application2D.h"
#include "Renderer2D.h"
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Application2D* app = new Application2D();
	app->runApp("OpenGL", 800, 600, false);
	delete app;
	return 0;
}