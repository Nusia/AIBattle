#pragma once

#include <irrlicht.h>
#include "cEventReceiver.h"

class cMouse;

class iGameState
{
public:
	virtual void Init( irr::IrrlichtDevice* device ) = 0;
	virtual void Update(irr::IrrlichtDevice* device ) = 0;
	virtual void Draw( irr::IrrlichtDevice* device ) = 0;
	virtual bool IsDone() = 0;
	virtual int GetNextState() = 0;
	virtual void ChangeState() = 0;
};

const enum{ PREGAME, INGAME };