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
		
		const unsigned HEIGHT = 480;
		const unsigned WIDTH = 480;

};
