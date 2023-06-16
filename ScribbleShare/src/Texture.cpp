#include "Texture.h"

SDL_Texture* Texture::texture_atlas_ = nullptr;

void Texture::Render(SDL_Renderer* renderer) {
	SDL_Rect srcrect;
	srcrect.x = sx_;
	srcrect.y = sy_;
	srcrect.w = sw_;
	srcrect.h = sh_;
	SDL_Rect dstrect;
	dstrect.x = dx_;
	dstrect.y = dy_;
	dstrect.w = dw_;
	dstrect.h = dh_;
	SDL_RenderCopy(renderer, texture_atlas_, &srcrect, &dstrect);
}

void Texture::SetAtlasLocation(uint32_t sx, uint32_t sy, uint32_t sw, uint32_t sh) {
	sx_ = sx;
	sy_ = sy;
	sw_ = sw;
	sh_ = sh;
}

void Texture::SetWindowLocation(uint32_t dx, uint32_t dy, uint32_t dw, uint32_t dh) {
	dx_ = dx;
	dy_ = dy;
	dw_ = dw;
	dh_ = dh;
}

bool Texture::LoadTextureAtlas(SDL_Renderer* renderer, const char* file_path) {
	texture_atlas_ = IMG_LoadTexture(renderer, file_path);
	if (!texture_atlas_)
		return false;
	return true;
}
