#include "engine.h"

#include <SDL3/SDL.h>

Application* Engine::app_instance_ = nullptr;

void Engine::SetApplication(Application* application)
{
	app_instance_ = application;
}

ResourceManager& Engine::GetResourceManager()
{
	if(!app_instance_)
	{
		SDL_Log("Application context not set for engine.\n");
		throw std::logic_error("Application context not set for engine.");
	}

	return app_instance_->resource_manager_;
}
