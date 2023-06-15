#include "Application.h"

Application::Application(const char* title, int width, int height)
	:app_should_run_(true), frame_(0) {
	if (!Init(title, width, height))
		exit(-1);
}

Application::~Application() {
	Terminate();
}

void Application::Run() {
	while (app_should_run_) {
		HandleEvents();
		Update();
		Render();
	}
}

void Application::HandleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		app_should_run_ = false;
		break;
	default:
		break;
	}
}

void Application::Update() {
	frame_++;
}

void Application::Render() {
	SDL_RenderClear(renderer_);

	/* Render Here */

	SDL_RenderPresent(renderer_);
}

bool Application::Init(const char* title, int width, int height) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "error: could not initialize SDL\n";
		return false;
	}

	window_ = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if (!window_) {
		std::cout << "error: could not create SDL_Window\n";
		return false;
	}

	renderer_ = SDL_CreateRenderer(window_, -1, 0);
	if (!renderer_) {
		std::cout << "error: could not create SDL_Renderer\n";
		return false;
	}

	return true;
}

void Application::Terminate() {
	SDL_DestroyWindow(window_);
	SDL_DestroyRenderer(renderer_);
	SDL_Quit();
}
