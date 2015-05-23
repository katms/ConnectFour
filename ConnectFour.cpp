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

	//calculate each tile's location
	for(unsigned i=0; i<COLUMNS; ++i) {
		for(unsigned j=0; j<ROWS; ++j) {
			//leave a row's worth of space at top
			board[i][j].x = i*TILE_LENGTH;
			board[i][j].y = (j+1)*TILE_LENGTH;
			
			board[i][j].w = TILE_LENGTH;
			board[i][j].h = TILE_LENGTH;
		}
	}
}

ConnectFour::~ConnectFour() {
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
		
		
		//draw
		for(unsigned i=0; i<COLUMNS; ++i) {
			for(unsigned j=0; j<ROWS; ++j) {
				SDL_RenderCopy(renderer, tile, NULL, &board[i][j]);
			}
		}
		
		//handle input
		switch(event.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if(SDL_BUTTON_LEFT == event.button.button) {
					int column_clicked = mouse.x/TILE_LENGTH;
				}
				break;
		}
	
		SDL_RenderPresent(renderer);
	}
}
