#include "cSoldier.h"

cSoldier::cSoldier()
{
	_pos = cPosition( 3, 3 );
}

void cSoldier::SetNewDestination(int x_cell, int y_cell)
{
	_destPos = cPosition( x_cell, y_cell );
}