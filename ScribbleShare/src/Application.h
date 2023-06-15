#pragma once

#include <SDL.h>

#include <iostream>

class Application {
public:
	Application(const char* title, int width, int height);
	~Application();

	void Run();
private:
	void HandleEvents();
	void Update();
	void Render();

	bool Init(const char* title, int width, int height);
	void Terminate();
private:
	unsigned int frame_;
	bool app_should_run_;
	SDL_Window* window_;
	SDL_Renderer* renderer_;
};