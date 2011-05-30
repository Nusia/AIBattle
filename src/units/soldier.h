#pragma once

#include "../helpers/position.h"

class Soldier
{
public:
	Soldier();
	void update();
	void draw();

	void set_new_destination( int x_cell, int y_cell );

private:
	Position pos_;
	Position dest_pos_;
};