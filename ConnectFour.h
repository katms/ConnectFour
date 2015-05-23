#include <SDL2/SDL.h>
#include "Tile.h"

class ConnectFour
{
	public:
		ConnectFour();
		~ConnectFour();
		
		void game_loop();

	private:
		SDL_Window *window;
		SDL_Renderer *renderer;
		SDL_Event event;
		SDL_Point mouse;
		
		bool running;
		
		//leave a space at the top
		const unsigned HEIGHT = (1+ROWS)*TILE_LENGTH;
		const unsigned WIDTH = COLUMNS*TILE_LENGTH;
		
		static const unsigned ROWS = 6;
		static const unsigned COLUMNS = 7;
		
		Tile board[COLUMNS][ROWS];
		SDL_Texture *tile;
		static const int TILE_LENGTH = 75;
		
		//loads a surface at path, sets colorkey, creates texture from surface and returns it
		SDL_Texture* load_texture_with_transparency(const char* path);
};
