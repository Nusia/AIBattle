#pragma once

#include "Math.h"
#include "map/map.h"

class AIBattle
{
private:
	int win_width;
	int win_height;

	int SCREEN_BPP;
	int FRAMES_PER_SECOND;

	Map* map;
	void init();
	void init_GL();

public:
	AIBattle();
	void handle_events( SDL_Event *event );
	void update();
	void draw();
};