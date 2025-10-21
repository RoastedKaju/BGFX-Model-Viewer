#include "application.h"
#include "utils/renderable.h"

Application::Application()
{
	is_running_ = false;
	window_ = nullptr;
	hwnd_ = nullptr;
	pd_ = bgfx::PlatformData{};
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

	// BGFX
	if (!InitBGFX())
	{
		SDL_Log("BGFX failed to initialize");
		SDL_DestroyWindow(window_);
		SDL_Quit();
		return false;
	}

	// Resouce manager
	resource_manager_.LoadShaders();
	resource_manager_.CreateFallbackTextures();
	resource_manager_.LoadMeshes();

	// Demo scene for model viewer
	CreateModelViewerScene();

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

			case SDL_EVENT_WINDOW_RESIZED:
				ResetView(event.window);
				break;

			default:
				break;
			}
		}

		bgfx::touch(0);

		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf(1, 1, 0x0f, "BGFX");

		resource_manager_.UpdateCamera();

		main_scene.Draw(0);

		bgfx::frame();
	}
}

bool Application::InitBGFX()
{
	pd_.nwh = hwnd_;

	bgfx::setPlatformData(pd_);

	bgfx::Init init;
	init.type = bgfx::RendererType::OpenGL;
	init.resolution.width = 800;
	init.resolution.height = 600;
	init.resolution.reset = BGFX_RESET_VSYNC;
	init.platformData = pd_;

	if (!bgfx::init(init)) {
		return false;
	}

	// Enable BGFX debug text
	bgfx::setDebug(BGFX_DEBUG_TEXT);

	bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x303030ff);
	bgfx::setViewRect(0, 0, 0, 800, 600);

	return true;
}

void Application::ResetView(const SDL_WindowEvent& window_event)
{
	const int new_width = window_event.data1;
	const int new_height = window_event.data2;
	bgfx::reset(new_width, new_height, BGFX_RESET_VSYNC);
	bgfx::setViewRect(0, 0, 0, new_width, new_height);
}

void Application::CreateModelViewerScene()
{
	auto& model = resource_manager_.GetModels().back();
	main_scene.AddRenderable(std::make_shared<Renderable>(model));

	main_scene.GetRenderables().begin()->get()->GetTransform().SetPosition(0.0f, 0.0f, -90.0f);
	//main_scene.GetRenderables().begin()->get()->GetTransform().SetScale(0.1f, 0.1f, 0.1f);
	//main_scene.GetRenderables().begin()->get()->GetTransform().SetRotation(bx::toRad(0.0f), bx::toRad(0.0f), bx::toRad(10.0f));
}
