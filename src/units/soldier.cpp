#include "soldier.h"

Soldier::Soldier()
{
	_pos = Position( 3, 3 );
}

void Soldier::set_new_destination(int x_cell, int y_cell)
{
	_dest_pos = Position( x_cell, y_cell );
}