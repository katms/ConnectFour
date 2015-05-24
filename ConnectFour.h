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
		
		//set to true between the time a button is clicked and released
		//waiting for X milliseconds wasn't working out
		bool wait_mouse = false;
		
		void draw();
		void handle_input();
		
		bool is_won() const;
		bool is_lost() const;
		bool gameover = false;
		
		//leave a space at the top
		const unsigned HEIGHT = (1+ROWS)*TILE_LENGTH;
		const unsigned WIDTH = COLUMNS*TILE_LENGTH;
		
		static const unsigned ROWS = 6;
		static const unsigned COLUMNS = 7;
		
		Tile board[COLUMNS][ROWS];
		SDL_Texture *tile;
		static const int TILE_LENGTH = 75;
		SDL_Texture *red;
		SDL_Texture *black;
		
		void drop_token(int column);
		//checks for and handles endgame, switches players
		void update();
		
		Tile::value current = Tile::RED; //red goes first
		
		//loads a surface at path, sets colorkey, creates texture from surface and returns it
		SDL_Texture* load_texture_with_transparency(const char* path);
};
