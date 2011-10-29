#include "cPosition.h"

cPosition::cPosition( const cPosition &orig )
{
	x = orig.x;
	y = orig.y;
}

const bool cPosition::operator== ( const cPosition &p ) const
{
	return (p.x == x && p.y == y );
}

const bool cPosition::operator!= ( const cPosition &p ) const
{
	return !( p.x == x && p.y == y );
}

std::ostream& operator<<( std::ostream& os, const cPosition p )
{
	os << "x: " << p.x << ", y: " << p.y;
	return os;
}

cPosition& cPosition::operator=( const cPosition &rhs )
{
	x = rhs.x;
	y = rhs.y;
	return *this;
}