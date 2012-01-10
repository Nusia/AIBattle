#pragma once

#include <irrlicht.h>
#include <vector>

using namespace irr;
using namespace core;

class cSoldierData
{
public:
	cSoldierData(){};
	void		SetPosition( vector2d<s32> pos ) { _position = pos; };
	void		SetPath( std::vector< vector2d<s32> > path ) { _vPath = path; };

	vector2d<s32>					GetPosition() { return _position; };
	std::vector< vector2d<s32> >	GetPath() { return _vPath; };

	void ClearPath(){ _vPath.clear(); };

	vector2d<s32>						_position;
	std::vector< vector2d<s32> >		_vPath;
};
