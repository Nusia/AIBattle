#include "i_game_State.h"
#include "../helpers/text_handler.h"

class PreGameState : public IGameState
{
private:
	bool _done;
	TTF_Font* font;

public:
	PreGameState(){};
	void init();
	void handle_input( SDL_Event* event );
	void update();
	void draw( SDL_Surface* screen );
	bool isDone();
	int get_next_state();
};