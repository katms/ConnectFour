#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Tile
{
	public:
		Tile() {}
		//relative coordinates
		Tile(int x, int y);
		
		enum value {EMPTY, RED, BLACK};
		bool is_empty() const;
		value get_color() const;
		void set_color(value new_color);
		
		bool operator==(const Tile& other) const;
		
		//set class texture (once) after setting up SDL,
		//since Tile is not responsible for loading it
		static void setup(SDL_Renderer *rn, SDL_Texture *tx, SDL_Texture *rd);
		
		void draw();
	
		static const int TILE_LENGTH = 75;
		
	private:
		SDL_Rect rect;
		value color = EMPTY;
		
		
		static SDL_Texture *texture;
		static SDL_Texture *red;
		
		static SDL_Renderer *renderer;


};
