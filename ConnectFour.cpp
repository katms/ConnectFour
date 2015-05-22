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
	tile = IMG_LoadTexture(renderer, tile_path);
	if(nullptr == tile) {
		printf("Could not load %s: %s\n", tile_path, SDL_GetError());
	}
		
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
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	
	SDL_Quit();
}

void ConnectFour::game_loop() {
	
	while(running) {
		SDL_PollEvent(&event);

		SDL_SetRenderDrawColor(renderer, 0x1c, 0x63, 0xdf, 0xff);
		SDL_RenderClear(renderer);
		
		if(SDL_QUIT == event.type) {
			running = false;
		}
		
		for(unsigned i=0; i<COLUMNS; ++i) {
			for(unsigned j=0; j<ROWS; ++j) {
				SDL_RenderCopy(renderer, tile, NULL, &board[i][j]);
			}
		}
	
		SDL_RenderPresent(renderer);
	}
}
