#include "pre_game_state.h"

void PreGameState::init()
{
	std::cout << "Initiating pregame state.\n";
	is_done_ = false;
	font = TextHandler::get_font( "../resources/fonts/larabiefont_rg.ttf", 16 );

	SDL_Surface* button_img = load_image("../resources/start_menu_button.png");
	SDL_Rect button_rect;
	button_rect.x = 250;
	button_rect.y = 300;
	button_rect.w = 175;
	button_rect.h = 50;

	Button* tmp_button = new Button( button_rect, button_img );

	MyEventHandler h1 = tmp_button->click_event.attach(
		this, &PreGameState::change_state);

	button_handler_.add_button( tmp_button );

	std::cout << "Pregame state ready.\n";
}

void PreGameState::handle_input( SDL_Event* event )
{
	if( event->type == SDL_MOUSEBUTTONDOWN )
		button_handler_.update( Position(event->motion.x, event->motion.y), event->type == SDL_MOUSEBUTTONDOWN );
	if( event->key.keysym.sym == SDLK_SPACE )
		is_done_ = true;
}

void PreGameState::update()
{
}

void PreGameState::draw( SDL_Surface* screen )
{
	button_handler_.draw( screen );
	TextHandler::render_text( 
		10, 10, 
		font,
		"Press 'Start game' to start the game.....", 
		0, 200, 0, 
		screen );
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