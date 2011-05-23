#pragma once

#include "../helpers/position.h"

class AStarNode
{
private:
	Position coordinate;
	AStarNode* parent;
	bool walkable;

public:
	AStarNode() {};
	AStarNode( 
		Position _coordinate,
		bool _walkable
		) 
		: coordinate(_coordinate), walkable(_walkable) {};

	void set_parent( AStarNode* p ) { parent = p; }
	AStarNode* get_parent() { return parent; }
	Position get_coordinate() { return coordinate; }
	void set_walkable( bool w ) { walkable = w; }
	bool is_walkable() { return walkable; }
};