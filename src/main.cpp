#include <iostream>

#include "core/application.h"
#include "core/engine.h"

int main()
{
	Application app;
	Engine::SetApplication(&app);
	
	if (!app.Create())
	{
		return 1;
	}

	app.Run();

	return 0;
}