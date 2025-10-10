#include <iostream>
#include <SDL3/SDL.h>

int main()
{
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("Failed to init SDL\n");
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("Viewer", 800, 600, SDL_WINDOW_RESIZABLE);

	if (!window)
	{
		SDL_Log("Failed to create window\n");
		return 1;
	}



	return 0;
}