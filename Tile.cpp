#include "Tile.h"

SDL_Renderer* Tile::renderer = nullptr;
SDL_Texture* Tile::texture = nullptr;
SDL_Texture* Tile::red = nullptr;

Tile::Tile(int x, int y) {
	rect.x = x*TILE_LENGTH;
	rect.y = (y+1)*TILE_LENGTH;
	
	rect.h = rect.w = TILE_LENGTH;
}

void Tile::draw() {
	switch(color) {
		case RED:
			SDL_RenderCopy(renderer, red, NULL, &rect);
			break;
		case BLACK:
			//left blank
		case EMPTY:
			break;
	}
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Tile::setup(SDL_Renderer *rn, SDL_Texture *tx, SDL_Texture *rd) {
	if(nullptr == renderer) { 
		renderer = rn;
	}
	
	if(nullptr == texture) {
		texture = tx;	
	}
	
	if(nullptr == red) {
		red = rd;
	}
}

bool Tile::is_empty() const {
	return (EMPTY == color);
}

Tile::value Tile::get_color() const {
	return color;
}

void Tile::set_color(value new_color) {
	if(EMPTY == color) {
		color = new_color;
	}
}

bool Tile::operator==(const Tile& other) const {
	return (color == other.color);
}
