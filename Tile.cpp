#include "Tile.h"

SDL_Renderer* Tile::renderer = nullptr;
SDL_Texture* Tile::texture = nullptr;
SDL_Texture* Tile::red = nullptr;
SDL_Texture* Tile::black = nullptr;


Tile::Tile(int x, int y) {
	rect.x = x*TILE_LENGTH;
	rect.y = (y+1)*TILE_LENGTH;
	
	rect.h = rect.w = TILE_LENGTH;
}

void Tile::draw() {
	switch(color) {
		case RED:
		case BLACK:
			SDL_RenderCopy(renderer, get_img(color), NULL, &rect);
			break;
		case EMPTY:
			//do nothing
			break;
	}
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Tile::setup(SDL_Renderer *rn, SDL_Texture *tx, SDL_Texture *rd, SDL_Texture *bk) {
	if(nullptr == renderer) { 
		renderer = rn;
	}
	
	if(nullptr == texture) {
		texture = tx;	
	}
	
	if(nullptr == red) {
		red = rd;
	}
	
	if(nullptr == black) {
		black = bk;
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

Tile::value Tile::opposite(value color) {
	switch(color) {
		case RED:
			return BLACK;
		case BLACK:
			return RED;
		default:
			return EMPTY;
	}
}

bool Tile::operator==(const Tile& other) const {
	return (color == other.color);
}

SDL_Texture* Tile::get_img(value v) {
	switch(v) {
		case RED:
			return red;
		case BLACK:
			return black;
		case EMPTY:
			return texture;
	}
}
