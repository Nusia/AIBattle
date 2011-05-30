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
	Map map;
	std::vector< Position > tmp_list_;
};