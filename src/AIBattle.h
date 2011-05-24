#pragma once

#include "Math.h"
#include "map/map.h"
#include "AI/a_star.h"

class AIBattle
{
private:
	Map map;
	int win_width;
	int win_height;

	SDL_Surface* screen;
	const int SCREEN_BPP;
	const int FRAMES_PER_SECOND;

	Position _unit_pos;
	std::vector< Position > _tmp_list;

	void init_GL();
	void init();

public:
	AIBattle();
	void handle_event( SDL_Event *event );
	void update();
	void draw();
};