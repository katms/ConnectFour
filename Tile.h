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
		
		static value opposite(value color);

		
		bool operator==(const Tile& other) const;
		
		//set class texture (once) after setting up SDL,
		//since Tile is not responsible for loading it
		static void setup(SDL_Renderer *rn, SDL_Texture *tx, SDL_Texture *rd, SDL_Texture *bk);
		
		void draw();
	
		static const int TILE_LENGTH = 75;
		static const int BORDER_LENGTH = TILE_LENGTH/2 - 20; //whitespace length
		
		
		static SDL_Texture* get_img(value v);
		
		
		//draw the token falling between the top and the goal
		struct Falling
		{
			Falling(Tile& t):
				goal(t)
			{
				location.x = t.rect.x;
				location.y = 0;
				location.h = location.w = Tile::TILE_LENGTH;
			}
			
			SDL_Rect location;
			Tile& goal;
			value& color = goal.color;
		};
		
	private:
		SDL_Rect rect;
		value color = EMPTY;
		
		
		static SDL_Texture *texture;
		static SDL_Texture *red;
		static SDL_Texture *black;
		
		static SDL_Renderer *renderer;


};
