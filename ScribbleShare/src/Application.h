#pragma once

#include "Texture.h"
#include "Canvas.h"

#include <iostream>
#include <vector>
#include <fstream>

class Application {
public:
	void Run(const char* title, int width, int height);
	static Application* GetInstance() { 
		if (!instance_)
			instance_ = new Application();
		return instance_;
	}
private:
	Application() = default;
	~Application() = default;
	static Application* instance_;

	/* main runtime loop */
	bool Init(const char* title, int width, int height);
	void HandleEvents();
	void Update();
	void Render();
	void Terminate();
private:
	bool LoadLayout(const char* file_path);
	void RenderUserInterface();
	void RenderCanvas();
private:
	unsigned int frame_ = 0;
	bool app_should_run_ = true;
private:
	// todo: Sound data
	struct SceneData {
		std::vector<Texture*> textures;
		Canvas* active_canvas = nullptr;
	} scenedata_;

	SDL_Window* window_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;
	SDL_Surface* surface_ = nullptr;
};