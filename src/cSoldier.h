#pragma once

#include "cPosition.h"

class cSoldier
{
public:
	cSoldier();
	void Update();
	void Draw();

	void SetNewDestination( int x_cell, int y_cell );

private:
	cPosition _pos;
	cPosition _destPos;
};