#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <SDL3/SDL.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/bx.h>
#include <bx/platform.h>
#include <Windows.h>

#include "resource_manager.h"
#include "scene.h"

class Engine;

class Application
{
public:
	Application();
	~Application();

	bool Create();
	void Run();

private:
	bool InitBGFX();
	void ResetView(const SDL_WindowEvent& window_event);

	void CreateModelViewerScene();

	bool is_running_;

	SDL_Window* window_;
	HWND hwnd_;

	bgfx::PlatformData pd_;

	ResourceManager resource_manager_;
	Scene main_scene;

	friend class Engine;
};

#endif // !APPLICATION_H_
