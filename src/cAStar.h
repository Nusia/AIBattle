#pragma once

#include <irrlicht.h>
#include <ITimer.h>
#include "Math.h"

#include "cAStarNode.h"
#include "cMap.h"
#include "cMapPositionHelper.h"

using namespace irr;
using namespace core;

class cAStar
{
public:
	cAStar( std::vector< std::vector<int> > map, std::vector<vector2d<s32>> units_list );
	std::vector<vector2d<s32>> GetBestPath( vector2d<s32> start_pos, vector2d<s32> goal_pos );

private:
	int _rgGScore[MAP_COLS][MAP_ROWS];
	int _rgHScore[MAP_COLS][MAP_ROWS];
	int _rgFScore[MAP_COLS][MAP_ROWS];

	cAStarNode* _prgPathMap[MAP_COLS][MAP_ROWS];

	std::vector<vector2d<s32>> _vClosedList;
	std::vector<vector2d<s32>> _vOpenList;
	std::vector<vector2d<s32>> _vCompletePath;

	vector2d<s32> _posStart;
	vector2d<s32> _posGoal;

	int _nStartTime;

	int			_heuristicEstimateOfDistance ( vector2d<s32> start, vector2d<s32> goal);
	double		_distanceBetween ( vector2d<s32> coord_1, vector2d<s32> coord_2 );
	vector2d<s32>	_getLowestFInOpenList();
	bool		_isCoordInCompletePath( vector2d<s32> coord );
	bool		_isCoordInOpenList( vector2d<s32> coord );
	bool		_isCoordInClosedList( vector2d<s32> coord );
	void		_reconstuctPath(vector2d<s32> goalNode);
	std::vector<vector2d<s32>> 
				_getNeighbors(vector2d<s32> coordinate);
};

