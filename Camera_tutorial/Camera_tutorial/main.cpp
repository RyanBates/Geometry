#include "Window.h"
#include "Geometry.h"

int main()
{
	Window* app = new Geometry();
	if (app->startup())
		app->run();
	app->shutdown();
	

	return 0;
}