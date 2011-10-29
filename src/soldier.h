#pragma once

#include "cPosition.h"

class Soldier
{
public:
	Soldier();
	void Update();
	void Draw();

	void SetNewDestination( int x_cell, int y_cell );

private:
	cPosition _pos;
	cPosition _destPos;
};