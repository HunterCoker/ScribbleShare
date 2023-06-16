#include "Application.h"

#define YAML_CPP_STATIC_DEFINE
#include <yaml-cpp/yaml.h>

Application* Application::instance_ = nullptr;

void Application::Run(const char* title, int width, int height) {
	if (!Init(title, width, height)) exit(-1);
	
	while (app_should_run_) {
		HandleEvents();
		Update();
		Render();
	}

	Terminate();
}

bool Application::Init(const char* title, int width, int height) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		SDL_Log("error: failed to initialize SDL: %s", SDL_GetError());
		return false;
	}

	window_ = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if (!window_) {
		SDL_Log("error: failed to create window: %s", SDL_GetError());
		return false;
	}
	surface_ = SDL_GetWindowSurface(window_);

	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer_) {
		SDL_Log("error: failed to create renderer: %s", SDL_GetError());
		return false;
	}
	SDL_SetRenderDrawColor(renderer_, 0x00, 0x00, 0x00, 0xFF);

	if (!Texture::LoadTextureAtlas(renderer_, "assets/textures/texture_atlas.png")) {
		SDL_Log("error: failed to load texture: %s", SDL_GetError());
		return false;
	}
	LoadLayout("layout.yml");

	return true;
}

void Application::HandleEvents() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			app_should_run_ = false;
			break;
		default:
			break;
		}
	}
}

void Application::Update() {
	frame_++;

	// handle input and mouse picking
}

void Application::Render() {
	SDL_RenderClear(renderer_);
	
	RenderUserInterface();
	RenderCanvas();

	SDL_RenderPresent(renderer_);
}

void Application::Terminate() {
	SDL_DestroyWindow(window_);
	SDL_DestroyRenderer(renderer_);
	SDL_Quit();
}

bool Application::LoadLayout(const char* file_path) {
	YAML::Node layout;
	try
	{
		layout = YAML::LoadFile(file_path);
	}
	catch (YAML::ParserException e)
	{
		std::cerr << "error: failed to load layout: " << e.what() << std::endl;
		return false;
	}

	auto fixed_data = layout["fixed"];
	if (!fixed_data) return false;
	for (auto node : fixed_data) {
		Texture* t = new Texture;

		auto atlas_location = node["atlas_location"];
		int sx = atlas_location[0].as<int>();
		int sy = atlas_location[1].as<int>();
		int sw = atlas_location[2].as<int>();
		int sh = atlas_location[3].as<int>();
		t->SetAtlasLocation(sx, sy, sw, sh);

		auto window_location = node["window_location"];
		int dx = window_location[0].as<int>();
		int dy = window_location[1].as<int>();
		int dw = window_location[2].as<int>();
		int dh = window_location[3].as<int>();
		t->SetWindowLocation(dx, dy, dw, dh);

		scenedata_.textures.push_back(t);
	}

	auto button_data = layout["button"];
	if (!button_data) return false;

	auto status_data = layout["status"];
	if (!status_data) return false;
	
	return true;
}

void Application::RenderUserInterface() {
	for (auto texture : scenedata_.textures) {
		texture->Render(renderer_);
	}
}

void Application::RenderCanvas() {

}
