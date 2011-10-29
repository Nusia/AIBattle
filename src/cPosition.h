#pragma once
//#include "gui/button.h"
//#include "game_states/pre_game_state.h"

#include <iostream>

class cPosition
{
	friend std::ostream& operator<<( std::ostream& os, const cPosition p );

public:
	int x, y;
	cPosition(){};
	cPosition( const cPosition &orig );
	cPosition( int _x, int _y) : x(_x), y(_y) {};

	const bool operator==( const cPosition &p ) const;
	const bool operator!=( const cPosition &p ) const;

	cPosition& operator=( const cPosition &rhs );
	//std::ostream& operator<<( std::ostream& os );
};