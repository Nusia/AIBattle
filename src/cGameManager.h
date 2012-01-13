#pragma once

#include <irrlicht.h>
#include "cSoldier.h"
#include "cMap.h"

class cGameManager
{
public:
	cGameManager() {};
	void Init();
	void InGameUpdate( irr::IrrlichtDevice* device );

	cMap*			GetMap() const { return _pMap; };
	cSoldier*		GetPlayer( int playerNr ) const;

private:
	cMap*			_pMap;
	cSoldier*		_pPlayer01;
	cSoldier*		_pPlayer02;
};
