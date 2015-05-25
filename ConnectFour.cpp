#include "ConnectFour.h"
#include <stdio.h>
#include <SDL2/SDL_image.h>

ConnectFour::ConnectFour() {
	running = true;
	
	//init
	if(SDL_Init(SDL_INIT_VIDEO)!=0) {
		printf("Could not initialize: %s\n", SDL_GetError());
		running = false;
	}
	
	//create window
	if(running) {
		window=SDL_CreateWindow("ConnectFour", 200, 200, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
		
		if(nullptr == window) {
			printf("Could not create window: %s\n", SDL_GetError());
			running = false;
		}
	}
	
	//create renderer
	if(running) {
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		
		if(nullptr == renderer) {
			printf("Could not create renderer: %s\n", SDL_GetError());
			running = false;
		}
	}
	const char *tile_path = "Images/tile.png";
	tile = load_texture_with_transparency(tile_path);
	
	red = load_texture_with_transparency("Images/red.png");
	black = load_texture_with_transparency("Images/black.png");


	//calculate each tile's location
	for(unsigned i=0; i<COLUMNS; ++i) {
		for(unsigned j=0; j<ROWS; ++j) {
			board[i][j] = Tile(i,j);
		}
	}
	
	Tile::setup(renderer, tile, red, black);
	
	cursor.y = 0;
	cursor.w = cursor.h = Tile::TILE_LENGTH;
}

ConnectFour::~ConnectFour() {
	SDL_DestroyTexture(red);
	SDL_DestroyTexture(black);
	SDL_DestroyTexture(tile);

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	
	SDL_Quit();
}

SDL_Texture* ConnectFour::load_texture_with_transparency(const char* path) {
	SDL_Texture *texture;
	SDL_Surface *surface = IMG_Load(path);
	if(nullptr == surface) {
		printf("Could not load %s: %s\n", path, SDL_GetError());
		texture = nullptr;
	}
	
	else {
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xff, 0xff, 0xff));
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		if(nullptr == texture) {
			printf("Could not create texture for %s: %s\n", path, SDL_GetError());
		}
		
		SDL_FreeSurface(surface);
	}
	return texture;
}

void ConnectFour::game_loop() {
	
	while(running) {
		SDL_PollEvent(&event);
		SDL_GetMouseState(&mouse.x, &mouse.y);

		SDL_SetRenderDrawColor(renderer, 0x1c, 0x63, 0xdf, 0xff);
		SDL_RenderClear(renderer);
		
		draw();
		
		handle_input();
		
		
	
		SDL_RenderPresent(renderer);
	}
}

void ConnectFour::draw() {
	for(const auto& f : falling) {
		SDL_RenderCopy(renderer, Tile::get_img(f.color), NULL, &(f.location));
	}


	for(unsigned i=0; i<COLUMNS; ++i) {
		for(unsigned j=0; j<ROWS; ++j) {
			board[i][j].draw();
		}
	}
	
	if(!gameover) {
		const int new_x = mouse.x - Tile::TILE_LENGTH/2;
	
		if(-Tile::BORDER_LENGTH < new_x && new_x + cursor.w < WIDTH+Tile::BORDER_LENGTH) {
			cursor.x = new_x;
		}
		
		SDL_RenderCopy(renderer, Tile::get_img(current), NULL, &cursor);
	}
}

void ConnectFour::handle_input() {
	switch(event.type) {
		case SDL_QUIT:
			running = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if(SDL_BUTTON_LEFT == event.button.button && !wait_mouse) {
				if(!gameover) {	
					int column_clicked = mouse.x/Tile::TILE_LENGTH;
						if(board[column_clicked][0].is_empty()) {
							drop_token(column_clicked);
							wait_mouse = true;
							update();
						}
				}
			}
			break;
		case SDL_MOUSEBUTTONUP:
			wait_mouse = false;
			break;
	}
}

void ConnectFour::update() {
	//check if the last move won the game
	if(is_won()) {
		printf("You win!\n");
		gameover = true;
	}
	
	else if(is_lost()) {
		printf("No more possible moves\n");
		gameover = true;
	}
	
	else { //next turn
		current = Tile::opposite(current);
	}
}

void ConnectFour::drop_token(int column) {
	//assume at least one empty space
	for(int i = ROWS-1; i >= 0; --i) {
		if(board[column][i].is_empty()) {
			board[column][i].set_color(current);
			falling.push_back(Tile::Falling(board[column][i]));
			return;
		}
	}
}

bool ConnectFour::is_won() const {
	for(unsigned i=0; i<COLUMNS; ++i) {
		for(unsigned j=0; j<ROWS; ++j) {
		
			//skip lines starting with an empty tile
			if(board[i][j].get_color()!=current) {
				continue;
			}
		
			if(i<COLUMNS-3) {
				if(board[i][j]==board[i+1][j] && 
					board[i+1][j]==board[i+2][j] && 
					board[i+2][j]==board[i+3][j]) {
					return true;
				}
				
				//check downward diagonal
				if(j<ROWS-3 &&
					board[i][j]==board[i+1][j+1] &&
					board[i+1][j+1]==board[i+2][j+2] &&
					board[i+2][j+2]==board[i+3][j+3]) {
						return true;
				}
				
				//check upward diagonal
				if(j>=3 &&
					board[i][j]==board[i+1][j-1] &&
					board[i+1][j-1]==board[i+2][j-2] &&
					board[i+2][j-2]==board[i+3][j-3]) {
						return true;
				}
				
			}
			
			//check columns
			if(j<ROWS-3 &&
				board[i][j]==board[i][j+1] &&
				board[i][j+1]==board[i][j+2] &&
				board[i][j+2]==board[i][j+3]) {
				return true;	
			}
		}
	}
	
	//exhausted all possibilities
	return false;
}

bool ConnectFour::is_lost() const {
	//check for at least one empty column
	for(unsigned i=0; i<COLUMNS; ++i) {
		if(board[i][0].get_color()==Tile::EMPTY) {
			return false;
		}
	}
	return true;
}

