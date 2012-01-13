#include "cSoldier.h"

cSoldier::cSoldier()
{
	_nUpdateFrequency = 25;
	_pSoldierData = new cSoldierData();
	_pAISettings = new cAISettings( _pSoldierData );
}

void cSoldier::Update( IrrlichtDevice* device, cSoldierData* player02 )
{
	if( device->getTimer()->getTime() - _nTimeOfLastTick > _nUpdateFrequency )
	{
		TickOnPath();
		_nTimeOfLastTick = device->getTimer()->getTime();
	}
	_pAISettings->Update( player02 );
}

void cSoldier::TickOnPath()
{
	vector2d<s32> goalPosition( 
		_pSoldierData->_vPath.front().X * PIXEL_PER_MAPSQUARE, 
		_pSoldierData->_vPath.front().Y * PIXEL_PER_MAPSQUARE );

	vector2d<s32> soldierPosition = _pSoldierData->GetPosition();

	if( goalPosition.X > soldierPosition.X )
		soldierPosition.X += 1;
	else if( goalPosition.X < soldierPosition.X )
		soldierPosition.X -= 1;

	if( goalPosition.Y > soldierPosition.Y )
		soldierPosition.Y += 1;
	else if( goalPosition.Y < soldierPosition.Y )
		soldierPosition.Y -= 1;

	if( soldierPosition == goalPosition )
		if( _pSoldierData->_vPath.size() > 0 )
			_pSoldierData->_vPath.erase(_pSoldierData->_vPath.begin());
	
	_pSoldierData->SetPosition( soldierPosition );
}