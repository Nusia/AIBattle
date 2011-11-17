#pragma once

#include <irrlicht.h>
#include <ITimer.h>
#include "Math.h"

#include "cAStarNode.h"
#include "cMap.h"

class cAStar
{
public:
	cAStar( std::vector< std::vector<int> > map, std::vector<irr::core::vector2d<irr::s32>> units_list );
	std::vector<irr::core::vector2d<irr::s32>> GetBestPath( irr::core::vector2d<irr::s32> start_pos, irr::core::vector2d<irr::s32> goal_pos );

private:
	int _rgGScore[MAP_COLS][MAP_ROWS];
	int _rgHScore[MAP_COLS][MAP_ROWS];
	int _rgFScore[MAP_COLS][MAP_ROWS];

	cAStarNode* _prgPathMap[MAP_COLS][MAP_ROWS];

	std::vector<irr::core::vector2d<irr::s32>> _vClosedList;
	std::vector<irr::core::vector2d<irr::s32>> _vOpenList;
	std::vector<irr::core::vector2d<irr::s32>> _vCompletePath;

	irr::core::vector2d<irr::s32> _posStart;
	irr::core::vector2d<irr::s32> _posGoal;

	int _nStartTime;

	int			_heuristicEstimateOfDistance ( irr::core::vector2d<irr::s32> start, irr::core::vector2d<irr::s32> goal);
	double		_distanceBetween ( irr::core::vector2d<irr::s32> coord_1, irr::core::vector2d<irr::s32> coord_2 );
	irr::core::vector2d<irr::s32>	_getLowestFInOpenList();
	bool		_isCoordInCompletePath( irr::core::vector2d<irr::s32> coord );
	bool		_isCoordInOpenList( irr::core::vector2d<irr::s32> coord );
	bool		_isCoordInClosedList( irr::core::vector2d<irr::s32> coord );
	void		_reconstuctPath(irr::core::vector2d<irr::s32> goalNode);
	std::vector<irr::core::vector2d<irr::s32>> 
				_getNeighbors(irr::core::vector2d<irr::s32> coordinate);
};