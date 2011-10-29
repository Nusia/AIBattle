#pragma once

#include "SDL.h"
#include "Math.h"

#include "../helpers/cPosition.h"
#include "cAStarNode.h"
#include "../map/cMap.h"

class cAStar
{
public:
	cAStar( std::vector< std::vector<int> > map, std::vector<cPosition> units_list );
	std::vector<cPosition> GetBestPath( cPosition start_pos, cPosition goal_pos );

private:
	int _rgGScore[MAP_COLS][MAP_ROWS];
	int _rgHScore[MAP_COLS][MAP_ROWS];
	int _rgFScore[MAP_COLS][MAP_ROWS];

	cAStarNode* _prgPathMap[MAP_COLS][MAP_ROWS];

	std::vector<cPosition> _vClosedList;
	std::vector<cPosition> _vOpenList;
	std::vector<cPosition> _vCompletePath;

	cPosition _posStart;
	cPosition _posGoal;

	int _nStartTime;

	int			_heuristicEstimateOfDistance ( cPosition start, cPosition goal);
	double		_distanceBetween ( cPosition coord_1, cPosition coord_2 );
	cPosition	_getLowestFInOpenList();
	bool		_isCoordInCompletePath( cPosition coord );
	bool		_isCoordInOpenList( cPosition coord );
	bool		_isCoordInClosedList( cPosition coord );
	void		_reconstuctPath(cPosition goalNode);
	std::vector<cPosition> 
				_getNeighbors(cPosition coordinate);
};