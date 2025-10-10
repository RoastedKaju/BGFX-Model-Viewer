#include <iostream>

#include "core/application.h"

int main()
{
	Application app;
	
	if (!app.Create())
	{
		return 1;
	}

	app.Run();

	return 0;
}