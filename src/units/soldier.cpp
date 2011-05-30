#include "soldier.h"

Soldier::Soldier()
{
	pos_ = Position( 3, 3 );
}

void Soldier::set_new_destination(int x_cell, int y_cell)
{
	dest_pos_ = Position( x_cell, y_cell );
}