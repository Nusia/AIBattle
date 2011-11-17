#pragma once

#include <iostream>
#include <irrlicht.h>
#include <vector>

using namespace irr;
using namespace core;

class cSoldier
{
public:
	cSoldier();
	void Update( IrrlichtDevice* device );

	void		SetPosition( vector2d<s32> pos ) { _position = pos; };
	void		SetPath( std::vector< vector2d<s32> > path ) { _vPath = path; };
	void		SetUpdateFrequency( u32 newFrequency ) { _nUpdateFrequency = newFrequency; };

	vector2d<s32>					GetPosition() { return _position; };
	std::vector< vector2d<s32> >	GetPath() { return _vPath; };

	void ClearPath();

private:
	//Funcs
	//-----
	void		TickOnPath();

	// Vars
	//-----
	vector2d<s32>						_position;
	std::vector< vector2d<s32> >		_vPath;

	u32									_nTimeOfLastTick;
	u32									_nUpdateFrequency;
};

