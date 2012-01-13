#ifndef _SOLDIER_H_
#define _SOLDIER_H_

#define PIXELS_PER_MAPSQUARE 10

#include <iostream>
#include <irrlicht.h>
#include <vector>
#include "cAISettings.h"
#include "cSoldierData.h"

#define PIXEL_PER_MAPSQUARE 10

using namespace irr;
using namespace core;

class cSoldier
{
public:
	cSoldier();
	void Update( IrrlichtDevice* device, cSoldierData* player02 );

	void		SetPosition( vector2d<s32> pos ){ _pSoldierData->SetPosition(pos); };
	void		SetPath( std::vector<vector2d<s32>> path ){ _pSoldierData->SetPath(path); };
	void		SetUpdateFrequency( u32 newFrequency ){ _nUpdateFrequency = newFrequency; };

	vector2d<s32>					GetPosition(){ return _pSoldierData->GetPosition(); };
	std::vector<vector2d<s32>>		GetPath(){ return _pSoldierData->GetPath(); };
	cAISettings*					GetAISettings(){ return _pAISettings; };

	void ClearPath(){ _pSoldierData->ClearPath(); };

	cSoldierData*	GetSoldierData(){ return _pSoldierData; };

private:
	//Funcs
	void		TickOnPath();

	// Vars
	u32									_nTimeOfLastTick;
	u32									_nUpdateFrequency;

	cSoldierData*						_pSoldierData;
	cAISettings*						_pAISettings;
};

#endif

