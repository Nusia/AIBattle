#include "cMouse.h"

cMouse::cMouse()
{
	_posCurrent = cPosition(0, 0);
	_posPrev = cPosition(0, 0);
}

void cMouse::Update()
{
	_posPrev = _posCurrent;
	SDL_GetMouseState( &_posCurrent.x, &_posCurrent.y );
}

void cMouse::HandleEvent( SDL_Event* event )
{
}

cPosition cMouse::GetCurrentPos()
{
	return _posCurrent;
}

cPosition cMouse::GetPrevPos()
{
	return _posPrev;
}

cPosition cMouse::DeltaPosFromLastUpdate()
{
	return cPosition( _posCurrent.x - _posPrev.x, _posCurrent.y - _posPrev.y );
}