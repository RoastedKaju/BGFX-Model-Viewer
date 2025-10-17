#ifndef ENGINE_H_
#define ENGINE_H_

#include <bgfx/bgfx.h>

#include "application.h"
#include "resource_manager.h"

class Engine
{
public:
	static void SetApplication(Application* application);

	static ResourceManager& GetResourceManager();

	static bgfx::ProgramHandle GetBasicShaderProgramHandle();

private:
	static Application* app_instance_;
};

#endif // !ENGINE_H_
