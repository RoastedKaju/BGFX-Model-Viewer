#ifndef ENGINE_H_
#define ENGINE_H_

#include "application.h"
#include "resource_manager.h"

class Engine
{
public:
	static void SetApplication(Application* application);

	static ResourceManager& GetResourceManager();

private:
	static Application* app_instance_;
};

#endif // !ENGINE_H_
