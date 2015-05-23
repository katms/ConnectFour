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
		SDL_Point mouse;
		
		bool running;
		
		const unsigned HEIGHT = (1+ROWS)*TILE_LENGTH;
		const unsigned WIDTH = COLUMNS*TILE_LENGTH;
		
		static const unsigned ROWS = 6;
		static const unsigned COLUMNS = 7;
		
		SDL_Rect board[COLUMNS][ROWS];
		SDL_Texture *tile;
		static const int TILE_LENGTH = 75;
		
		SDL_Texture* load_texture_with_transparency(const char* path);
};
