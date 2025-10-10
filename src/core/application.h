#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <SDL3/SDL.h>
#include <Windows.h>

class Application
{
public:
	Application();
	~Application();

	bool Create();
	void Run();
private:
	bool is_running_;
	SDL_Window* window_;
	HWND hwnd_;
};

#endif // !APPLICATION_H_
