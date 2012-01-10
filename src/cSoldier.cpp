#include "cSoldier.h"

cSoldier::cSoldier()
{
	_nUpdateFrequency = 250;
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
	if( _pSoldierData->_vPath.size() > 0 )
	{
		_pSoldierData->SetPosition( vector2d<s32>( _pSoldierData->_vPath.front().X, _pSoldierData->_vPath.front().Y ) );
		_pSoldierData->_vPath.erase(_pSoldierData->_vPath.begin());
	}
}