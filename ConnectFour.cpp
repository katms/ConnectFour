#include "ConnectFour.h"
#include <stdio.h>

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
	
	
		SDL_RenderPresent(renderer);
	}
}
