#include "application.h"

Application::Application()
{
	is_running_ = false;
	window_ = nullptr;
}

Application::~Application()
{
	if (window_)
	{
		SDL_DestroyWindow(window_);
		window_ = nullptr;
	}

	SDL_Quit();
}

bool Application::Create()
{
	// Initialize SDL
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("SDL failed to init.");
		return false;
	}

	// Create window
	window_ = SDL_CreateWindow("Viewer", 800, 600, SDL_WINDOW_RESIZABLE);

	if (!window_)
	{
		SDL_Log("Window creation failed.");
		SDL_Quit();
		return false;
	}

	// Backend window handle
	hwnd_ = (HWND)SDL_GetPointerProperty(SDL_GetWindowProperties(window_), SDL_PROP_WINDOW_WIN32_HWND_POINTER, NULL);

	if (!hwnd_)
	{
		SDL_Log("Failed to get window backend handle");
		SDL_DestroyWindow(window_);
		SDL_Quit();
		return false;
	}

	return true;
}

void Application::Run()
{
	is_running_ = true;

	while (is_running_)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
				is_running_ = false;
				break;

			case SDL_EVENT_QUIT:
				break;

			default:
				break;
			}
		}
	}
}