#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <SDL3/SDL.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/bx.h>
#include <bx/platform.h>
#include <Windows.h>

class Application
{
public:
	Application();
	~Application();

	bool Create();
	void Run();

private:
	bool InitBGFX();

	bool is_running_;
	SDL_Window* window_;
	HWND hwnd_;
	bgfx::PlatformData pd_;
};

#endif // !APPLICATION_H_
