#include <SDL2/SDL.h>
#include "Tile.h"
#include <array>

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
		
		unsigned ticks;
		static const unsigned DELAY = 20;
		
		void draw();
		void handle_input();
		void update();
		
		bool is_won() const;
		bool is_lost() const;
		
		enum {PLAYING, GAMEOVER} state;
		
		//leave a space at the top
		const int HEIGHT = (1+ROWS)*Tile::TILE_LENGTH;
		const int WIDTH = COLUMNS*Tile::TILE_LENGTH;
		
		static const unsigned ROWS = 6;
		static const unsigned COLUMNS = 7;
		
		Tile board[COLUMNS][ROWS];
		SDL_Texture *tile;
		SDL_Texture *red;
		SDL_Texture *black;
		
		void drop_token(int column);
		//checks for and handles endgame, switches players
		void update_game_state();
		
		Tile::value human;
		Tile::value computer;
		
		Tile::value current;
		
		//draw the currently playing token at the top of the board as the cursor moves
		SDL_Rect cursor;
		SDL_Texture *cursor_tx;
		
		//loads a surface at path, sets colorkey, creates texture from surface and returns it
		SDL_Texture* load_texture_with_transparency(const char* path);
		
		//only one animation per column
		//if falling[c] is null, c has none
		std::array<Tile::Falling*, COLUMNS> falling;
};
