#include "ConnectFour.h"
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>

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
	
	falling.fill(nullptr);
	
	state = CHOOSE;
	
	current = human;
	
	ticks = SDL_GetTicks();
}

ConnectFour::~ConnectFour() {

	for(auto& f: falling) {
		if(f) {
			delete f;
		}
	}

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
	
	while(running && SDL_QUIT != event.type) {
		SDL_PollEvent(&event);
		SDL_GetMouseState(&mouse.x, &mouse.y);

		SDL_SetRenderDrawColor(renderer, 0x1c, 0x63, 0xdf, 0xff);
		SDL_RenderClear(renderer);
		
		draw();
		
		if(ticks + DELAY < SDL_GetTicks()) {
			handle_input();
			update();
			ticks = SDL_GetTicks();
		}
	
	
		SDL_RenderPresent(renderer);
	}
}

void ConnectFour::draw() {

	switch(state) {
		case CHOOSE:
			//split the window
			SDL_Rect right, left;
			right.y = left.y = 0;
			right.h = left.h = HEIGHT;
			right.x = 0;
			
			//fill all space
			right.w = left.w = WIDTH/2;
			left.w += WIDTH%2;
			left.x = WIDTH - right.w - 1;
			
			//draw right/red and left/black halves
			SDL_SetRenderDrawColor(renderer, 0xFF, 0x0B, 0x0B, 0xFF);
			SDL_RenderFillRect(renderer, &right);
			
			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
			SDL_RenderFillRect(renderer, &left);
			break;
		
		case PLAYING:
		case GAMEOVER:
			//draw falling tokens under the board
			for(const auto& f : falling) {
				if(f) {
					SDL_RenderCopy(renderer, Tile::get_img(f->color), NULL, &(f->location));
				}
			}

			//draw board
			for(unsigned i=0; i<COLUMNS; ++i) {
				for(unsigned j=0; j<ROWS; ++j) {
					board[i][j].draw();
				}
			}
	
			//draw player
			if(PLAYING == state && current == human) {
				const int new_x = mouse.x - Tile::TILE_LENGTH/2;
	
				if(-Tile::BORDER_LENGTH < new_x && new_x + cursor.w < WIDTH+Tile::BORDER_LENGTH) {
					cursor.x = new_x;
				}
		
				SDL_RenderCopy(renderer, Tile::get_img(human), NULL, &cursor);
			}
			break;
	}
}

void ConnectFour::handle_input() {
	switch(event.type) {
		case SDL_QUIT:
			running = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if(SDL_BUTTON_LEFT == event.button.button && !wait_mouse) {
				switch(state) {
					case CHOOSE:
						if(mouse.x < WIDTH/2)	human = Tile::RED;
						else 					human = Tile::BLACK;
						computer = Tile::opposite(human);
						
						//choose who goes first
						if(rand()%2) current = human;
						else current = computer;
						
						
						state = PLAYING;
						wait_mouse = true;
						break;
					case PLAYING:
						if(human == current) {	
							int column_clicked = mouse.x/Tile::TILE_LENGTH;
							if(board[column_clicked][0].is_empty()) {
								drop_token(column_clicked);
								wait_mouse = true;
							}
						}
						break;
					default:
						break;
				}
			}
			break;
		case SDL_MOUSEBUTTONUP:
			wait_mouse = false;
			break;
		case SDL_KEYDOWN:
			for(auto& f : falling) {
				if(f) f->skip();
			}
			break;
	}
}

void ConnectFour::update() {
	switch(state) {
		case PLAYING:
		case GAMEOVER:
			for(auto& f: falling) {
				if(f) {
					f->update();
			
					//remove tokens that reached the goal
					if(f->is_done()) {
						delete f;
						f = nullptr;
					}
				}
			}
	
			//choose a random available column
			if(PLAYING == state && computer == current) {
				//an only be in state PLAYING if there is at least one possible move
				//start at a random column and iterate until one is found
				int move;
				for(move=rand(); !board[move%7][0].is_empty(); ++move);
				drop_token(move%7);
			}
			break;
		default:
			break;
	}
}

void ConnectFour::update_game_state() {
	//check if the last move won the game
	if(is_won()) {
		if(human == current)
			printf("You win!\n");
		else
			printf("You lose.\n");
		state = GAMEOVER;
	}
	
	else if(is_lost()) {
		printf("No more possible moves\n");
		state = GAMEOVER;
	}
	
	else { //next turn
		current = Tile::opposite(current);
	}
}

void ConnectFour::drop_token(int column) {

	if(!board[column][0].is_empty()) {
		return;
	}	

	for(int i = ROWS-1; i >= 0; --i) {
		if(board[column][i].is_empty()) {
			board[column][i].set_color(current);
			
			auto& ptr = falling[column];
			
			/* cancel animations in the same column 
			   so that if one column is quickly filled,
			   the top won't stop at its goal
			   while the first one is still falling through empty space
			*/
			if(ptr) {
				delete ptr;
				ptr = nullptr;
			}
			ptr = new Tile::Falling(board[column][i]);
			update_game_state();
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

