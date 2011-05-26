#pragma once

#include <iostream>

class Position
{
	friend std::ostream& operator<<( std::ostream& os, const Position p );

public:
	int x, y;
	Position(){};
	Position( const Position &orig );
	Position( int _x, int _y) : x(_x), y(_y) {};

	const bool operator==( const Position &p ) const;
	const bool operator!=( const Position &p ) const;

	Position& operator=( const Position &rhs );
	//std::ostream& operator<<( std::ostream& os );
};