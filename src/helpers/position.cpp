#include "position.h"

Position::Position( const Position &orig )
{
	x = orig.x;
	y = orig.y;
}

const bool Position::operator== ( const Position &p ) const
{
	return (p.x == x && p.y == y );
}

const bool Position::operator!= ( const Position &p ) const
{
	return !( p.x == x && p.y == y );
}

std::ostream& operator<<( std::ostream& os, const Position p )
{
	os << "x: " << p.x << ", y: " << p.y;
	return os;
}

Position& Position::operator=( const Position &rhs )
{
	x = rhs.x;
	y = rhs.y;
	return *this;
}