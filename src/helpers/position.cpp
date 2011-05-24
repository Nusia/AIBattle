#include "position.h"

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