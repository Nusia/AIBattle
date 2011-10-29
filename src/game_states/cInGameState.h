#include "iGameState.h"
#include "../AI/cAStar.h"

class cInGameState : public iGameState
{
public:
	cInGameState();
	void Init();
	void HandleInput( SDL_Event* event );
	void Update();
	void Draw( SDL_Surface* screen );
	bool IsDone();
	int GetNextState();

private:
	//Variables
	//---------
	cMap map;
	std::vector< cPosition > tmp_list_;

	cPosition cam_pos_;
	
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