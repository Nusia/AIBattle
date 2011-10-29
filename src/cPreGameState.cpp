#include "cPreGameState.h"

void cPreGameState::Init()
{
	std::cout << "Initiating pregame state.\n";
	_bIsDone = false;
	_pFont = cTextHandler::GetFont( "resources/fonts/larabiefont_rg.ttf", 16 );

	SDL_Surface* button_img = cImageHelper::LoadImage("resources/pre_game/start_button.png");
	SDL_Rect button_rect;
	button_rect.x = 896;
	button_rect.y = 0;
	button_rect.w = 128;
	button_rect.h = 64;
	cButton* tmp_button = new cButton( button_rect, button_img );
	MyEventHandler h1 = tmp_button->ClickEvent.attach(
		this, &cPreGameState::ChangeState);
	_buttonHandler.AddButton( tmp_button );

	SDL_Surface* map_settings_button_img = cImageHelper::LoadImage("resources/pre_game/map_settings_button.png");
	SDL_Rect map_settings_button_rect;
	map_settings_button_rect.x = 10;
	map_settings_button_rect.y = 32;
	map_settings_button_rect.w = 128;
	map_settings_button_rect.h = 32;
	cButton* map_settings_button = new cButton( map_settings_button_rect, map_settings_button_img );
	MyEventHandler h2 = map_settings_button->ClickEvent.attach(
		this, &cPreGameState::_changeToMapSettings);
	_buttonHandler.AddButton( map_settings_button );

	SDL_Surface* ai_settings_button_img = cImageHelper::LoadImage("resources/pre_game/ai_settings_button.png");
	SDL_Rect ai_settings_button_rect;
	ai_settings_button_rect.x = 148;
	ai_settings_button_rect.y = 32;
	ai_settings_button_rect.w = 128;
	ai_settings_button_rect.h = 32;
	cButton* ai_settings_button = new cButton( ai_settings_button_rect, ai_settings_button_img );
	MyEventHandler h3 = ai_settings_button->ClickEvent.attach(
		this, &cPreGameState::_changeToAiSettings);
	_buttonHandler.AddButton( ai_settings_button );

	_pMapSettings = new cMapSettings();
	_pAiSettings = new cAISettings();
	_pActiveState = _pAiSettings;


	std::cout << "Pregame state ready.\n";
}

void cPreGameState::HandleInput( SDL_Event* event )
{
	if( event->type == SDL_MOUSEBUTTONDOWN )
		_buttonHandler.Update( cPosition(event->motion.x, event->motion.y), event->type == SDL_MOUSEBUTTONDOWN );
	if( event->key.keysym.sym == SDLK_SPACE )
		_bIsDone = true;

	_pActiveState->HandleInput( event );
}

void cPreGameState::Update()
{
	_pActiveState->Update();
}

void cPreGameState::Draw( SDL_Surface* screen )
{
	_buttonHandler.Draw( screen );
		
	_pActiveState->Draw( screen );
}

bool cPreGameState::IsDone()
{
	return _bIsDone;
}

int cPreGameState::GetNextState()
{
	return INGAME;
}

void cPreGameState::ChangeState()
{
	_bIsDone = true;
}