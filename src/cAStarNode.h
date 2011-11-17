#pragma once



class cAStarNode
{
private:
	irr::core::vector2d<irr::s32> coordinate;
	cAStarNode* parent;
	bool walkable;

public:
	cAStarNode() {};
	cAStarNode( 
		irr::core::vector2d<irr::s32> _coordinate,
		bool _walkable
		) 
		: coordinate(_coordinate), walkable(_walkable) {};

	void set_parent( cAStarNode* p ) { parent = p; }
	cAStarNode* get_parent() { return parent; }
	irr::core::vector2d<irr::s32> get_coordinate() { return coordinate; }
	void set_walkable( bool w ) { walkable = w; }
	bool is_walkable() { return walkable; }
};