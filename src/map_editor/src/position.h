#pragma once

class Position
{
public:
	int x, y;
	Position(){};
	Position( int _x, int _y) : x(_x), y(_y) {};

	const bool operator==( const Position &p ) const;
	const bool operator!=( const Position &p ) const;
};