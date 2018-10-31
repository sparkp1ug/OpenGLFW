#include "Application2D.h"

int main()
{
	Application2D* app = new Application2D();
	app->runApp("OpenGL", 800, 600, false);

	return 0;
}