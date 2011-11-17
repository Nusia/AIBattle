#include "cSoldier.h"

cSoldier::cSoldier()
{
	_nUpdateFrequency = 250;
}

void cSoldier::Update( IrrlichtDevice* device )
{
	if( device->getTimer()->getTime() - _nTimeOfLastTick > _nUpdateFrequency )
	{
		TickOnPath();
		_nTimeOfLastTick = device->getTimer()->getTime();
	}
}

void cSoldier::ClearPath()
{
	_vPath.clear();
}

void cSoldier::TickOnPath()
{
	if( _vPath.size() > 0 )
	{
		_position = vector2d<s32>( _vPath.front().X, _vPath.front().Y );
		_vPath.erase(_vPath.begin());
	}
}