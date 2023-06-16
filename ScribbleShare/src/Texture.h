#pragma once

#include <SDL.h>
#include <SDL_image.h>

class Texture {
public:
	Texture() = default;
	~Texture() = default;

	void Render(SDL_Renderer* renderer);

	void SetAtlasLocation(uint32_t sx, uint32_t sy, uint32_t sw, uint32_t sh);
	void SetWindowLocation(uint32_t dx, uint32_t dy, uint32_t dw, uint32_t dh);
public:
	static bool LoadTextureAtlas(SDL_Renderer* renderer, const char* file_path);
private:
	uint32_t sx_, sy_, sw_, sh_;
	uint32_t dx_, dy_, dw_, dh_;
	static SDL_Texture* texture_atlas_;
};