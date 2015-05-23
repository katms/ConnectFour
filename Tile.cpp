#include "Tile.h"

SDL_Renderer* Tile::renderer = nullptr;
SDL_Texture* Tile::texture = nullptr;

Tile::Tile(int x, int y) {
	rect.x = x*TILE_LENGTH;
	rect.y = (y+1)*TILE_LENGTH;
	
	rect.h = rect.w = TILE_LENGTH;
}

void Tile::draw() {
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Tile::setup(SDL_Renderer *rn, SDL_Texture *tx) {
	if(nullptr == renderer && nullptr == texture) {
		renderer = rn;
		texture = tx;
	}
}
