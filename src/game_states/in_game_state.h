#include "i_game_state.h"
#include "../AI/a_star.h"

class InGameState : public IGameState
{
public:
	InGameState();
	void init();
	void handle_input( SDL_Event* event );
	void update();
	void draw( SDL_Surface* screen );
	bool isDone();
	int get_next_state();

private:
	//Variables
	//---------
	Map map;
	std::vector< Position > tmp_list_;

	Position cam_pos_;
	
	SDL_Surface* character_player_01;
	SDL_Surface* character_player_02;
	SDL_Surface* stone_tile_low;
	SDL_Surface* stone_tile_high;
	SDL_Surface* shadow_north_east;
	SDL_Surface* shadow_east;
	SDL_Surface* shadow_south_east;
	SDL_Surface* shadow_south;
	SDL_Surface* shadow_south_west;
	SDL_Surface* shadow_west;
	SDL_Surface* shadow_north_west;
	SDL_Surface* shadow_north;
};