#include "soldier.h"

Soldier::Soldier()
{
	_pos = cPosition( 3, 3 );
}

void Soldier::SetNewDestination(int x_cell, int y_cell)
{
	_destPos = cPosition( x_cell, y_cell );
}