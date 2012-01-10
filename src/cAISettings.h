#ifndef _AISETTINGS_H_
#define _AISETTINGS_H_

#include <iostream>
#include "cSoldierData.h"
#include "Math.h"
#include "cMessageBoxInGame.h"

class cAISettings
{
public:
	cAISettings( cSoldierData* soldierData );
	void Init();
	void Update( cSoldierData* player02 );

	void SetToCloseAlertDistance( int distance );

private:
	//Functions
	int distanceBetweenPoints( irr::core::vector2d<irr::s32> p1, irr::core::vector2d<irr::s32> p2 );

	//Variables
	cSoldierData* _pSoldierData;

	int _nToCloseAlertDistance;
	bool _bToClose;

	char _cToCloseString[64];
	char _cNotToCloseString[64];
};

#endif