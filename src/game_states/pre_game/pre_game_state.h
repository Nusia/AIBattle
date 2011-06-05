#pragma once

#include "map_settings.h"
#include "ai_settings.h"
#include "../i_game_State.h"
#include "../../helpers/text_handler.h"
#include "../../gui/button.h"
#include "../../gui/button_handler.h"
#include "../../helpers/Position.h"
#include "../../helpers/image_helper.h"
#include "../../event_handler/event.h"

#define COLORKEY 255, 0, 255 //Your Transparent colour

//template <class Object> class Button;

class PreGameState : public IGameState
{
public:
	PreGameState(){};
	void change_state();
	void init();
	void handle_input( SDL_Event* event );
	void update();
	void draw( SDL_Surface* screen );
	bool isDone();
	int get_next_state();

private:
	void change_to_map_settings() { active_state_ = map_settings_; }
	void change_to_ai_settings() { active_state_ = ai_settings_; }

	IPreGame* active_state_;
	MapSettings* map_settings_;
	AISettings* ai_settings_;
	
	bool is_done_;
	TTF_Font* font;
	ButtonHandler button_handler_;	
};
