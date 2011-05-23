#include "position.h"

const bool Position::operator== ( const Position &p ) const
{
	return (p.x == x && p.y == y );
}

const bool Position::operator!= ( const Position &p ) const
{
	return !( p.x == x && p.y == y );
}