#include "pre_game_state.h"

void PreGameState::init()
{
	std::cout << "Initiating pregame state.\n";
	is_done_ = false;
	font = TextHandler::get_font( "../resources/fonts/larabiefont_rg.ttf", 16 );

	SDL_Surface* button_img = ImageHelper::load_image("../resources/pre_game/start_button.png");
	SDL_Rect button_rect;
	button_rect.x = 896;
	button_rect.y = 0;
	button_rect.w = 128;
	button_rect.h = 64;
	Button* tmp_button = new Button( button_rect, button_img );
	MyEventHandler h1 = tmp_button->click_event.attach(
		this, &PreGameState::change_state);
	button_handler_.add_button( tmp_button );

	SDL_Surface* map_settings_button_img = ImageHelper::load_image("../resources/pre_game/map_settings_button.png");
	SDL_Rect map_settings_button_rect;
	map_settings_button_rect.x = 10;
	map_settings_button_rect.y = 32;
	map_settings_button_rect.w = 128;
	map_settings_button_rect.h = 32;
	Button* map_settings_button = new Button( map_settings_button_rect, map_settings_button_img );
	MyEventHandler h2 = map_settings_button->click_event.attach(
		this, &PreGameState::change_to_map_settings);
	button_handler_.add_button( map_settings_button );

	SDL_Surface* ai_settings_button_img = ImageHelper::load_image("../resources/pre_game/ai_settings_button.png");
	SDL_Rect ai_settings_button_rect;
	ai_settings_button_rect.x = 148;
	ai_settings_button_rect.y = 32;
	ai_settings_button_rect.w = 128;
	ai_settings_button_rect.h = 32;
	Button* ai_settings_button = new Button( ai_settings_button_rect, ai_settings_button_img );
	MyEventHandler h3 = ai_settings_button->click_event.attach(
		this, &PreGameState::change_to_ai_settings);
	button_handler_.add_button( ai_settings_button );

	map_settings_ = new MapSettings();
	ai_settings_ = new AISettings();
	active_state_ = ai_settings_;


	std::cout << "Pregame state ready.\n";
}

void PreGameState::handle_input( SDL_Event* event )
{
	if( event->type == SDL_MOUSEBUTTONDOWN )
		button_handler_.update( Position(event->motion.x, event->motion.y), event->type == SDL_MOUSEBUTTONDOWN );
	if( event->key.keysym.sym == SDLK_SPACE )
		is_done_ = true;

	active_state_->handle_input( event );
}

void PreGameState::update()
{
	active_state_->update();
}

void PreGameState::draw( SDL_Surface* screen )
{
	button_handler_.draw( screen );
		
	active_state_->draw( screen );
}

bool PreGameState::isDone()
{
	return is_done_;
}

int PreGameState::get_next_state()
{
	return INGAME;
}

void PreGameState::change_state()
{
	is_done_ = true;
}