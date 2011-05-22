#pragma once

#include "Math.h"
#include "map/map.h"

class AIBattle
{
private:
	Map map;
	int win_width;
	int win_height;

	int SCREEN_BPP;
	int FRAMES_PER_SECOND;

	void init_GL();
	void init();

public:
	AIBattle();
	void handle_event( SDL_Event *event );
	void update();
	void draw();
};