#pragma once

#include "../helpers/cPosition.h"

class cAStarNode
{
private:
	cPosition coordinate;
	cAStarNode* parent;
	bool walkable;

public:
	cAStarNode() {};
	cAStarNode( 
		cPosition _coordinate,
		bool _walkable
		) 
		: coordinate(_coordinate), walkable(_walkable) {};

	void set_parent( cAStarNode* p ) { parent = p; }
	cAStarNode* get_parent() { return parent; }
	cPosition get_coordinate() { return coordinate; }
	void set_walkable( bool w ) { walkable = w; }
	bool is_walkable() { return walkable; }
};