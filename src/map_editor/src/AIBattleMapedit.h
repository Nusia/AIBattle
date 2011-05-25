#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <string>

#include "Math.h"
#include "map.h"

class AIBattleMapedit
{
private:
	Map map;
	int win_width;
	int win_height;

	int active_block_type;

	SDL_Surface* screen;
	SDL_Surface* msg;
	const int SCREEN_BPP;
	const int FRAMES_PER_SECOND;

	void init_GL();
	void init();

	TTF_Font *font;

	void RenderText(
		const TTF_Font *Font, 
		const float R, 
		const float G, 
		const float B, 
		const double& X, 
		const double& Y, 
		const double& Z, 
		const std::string& Text);


public:
	AIBattleMapedit();
	void handle_event( SDL_Event *event );
	void update();
	void draw();
};