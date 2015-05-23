#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Tile
{
	public:
		Tile() {}
		//relative coordinates
		Tile(int x, int y);
		
		//set class texture (once) after setting up SDL,
		//since Tile is not responsible for loading it
		static void setup(SDL_Renderer *rn, SDL_Texture *tx);
		
		void draw();
	
		static const int TILE_LENGTH = 75;
		
	private:
		SDL_Rect rect;
		
		static SDL_Texture *texture;
		static SDL_Renderer *renderer;


};
