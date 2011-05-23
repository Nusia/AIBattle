#pragma once

#include "../helpers/position.h"

class Soldier
{
private:
	Position _pos;
	Position _dest_pos;

public:
	Soldier();
	void update();
	void draw();

	void set_new_destination( int x_cell, int y_cell );
};