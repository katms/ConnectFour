#include <SDL2/SDL.h>

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
		
		bool running;
		
		const unsigned HEIGHT = ROWS*tile_length;
		const unsigned WIDTH = (1+COLUMNS)*tile_length;
		
		static const unsigned ROWS = 6;
		static const unsigned COLUMNS = 7;
		
		SDL_Rect board[COLUMNS][ROWS];
		SDL_Texture *tile;
		static const int tile_length = 200;
};
