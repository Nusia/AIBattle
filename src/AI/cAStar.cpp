#include "cAStar.h"

cAStar::cAStar( std::vector< std::vector<int> > map, std::vector<cPosition> units_list )
{
	std::vector<int> tmp;
	for( unsigned int col = 0; col < map.size(); ++col )
		for( unsigned int row = 0; row < map[0].size(); ++row )
		{
			_prgPathMap[col][row] = new cAStarNode( 
				cPosition(col, row), 
				map[col][row] == cMap::WALKABLE );
		}

		_prgPathMap[units_list[0].x][units_list[0].y]->set_walkable( false );
		//_prgPathMap[units_list[1].x][units_list[1].y]->set_walkable( false );
}

std::vector<cPosition> cAStar::GetBestPath( cPosition start_pos, cPosition goal_pos )
{	
	std::cout << "Calculating new path to " << start_pos << " using A*\n";

	_nStartTime = SDL_GetTicks();
	_posStart = start_pos;
	_posGoal = goal_pos;
	_vOpenList.push_back( start_pos );

	_rgGScore[start_pos.x][start_pos.y] = 0;
	_rgHScore[start_pos.x][start_pos.y] = _heuristicEstimateOfDistance( start_pos, goal_pos );
	_rgFScore[start_pos.x][start_pos.y] = _rgHScore[start_pos.x][start_pos.y];

	cPosition current_node_coord;
	std::vector<cPosition> neighbor_list;
	bool tentative_is_better;

	cPosition y_node_coord;

	while (!_vOpenList.empty())
	{
		//Get the "best" node from open_list
		current_node_coord = _getLowestFInOpenList();

		if( current_node_coord.x == goal_pos.x &&
			current_node_coord.y == goal_pos.y)
		{
			_reconstuctPath(current_node_coord);
			break;
		}

		//Add to closed_list
		_vClosedList.push_back(current_node_coord);

		//Remove from open_list
		int tmpPos;
		for ( unsigned int i = 0; i < _vOpenList.size(); ++i)
		{
			if(_vOpenList[i] == current_node_coord)
			{
				tmpPos = i;
				i = _vOpenList.size();
			}
		}
		_vOpenList.erase(_vOpenList.begin() + tmpPos);
		neighbor_list = _getNeighbors( current_node_coord );

		//Process all neighbors
		for(std::vector<cPosition>::const_iterator y_node_coord = neighbor_list.begin(); y_node_coord != neighbor_list.end(); ++y_node_coord )
		{
			if( !_isCoordInClosedList( (*y_node_coord) ) )
			{
				//Get tentative g score
				int tentative__rgGScore = 
					_rgGScore[current_node_coord.x][current_node_coord.y] + 
					(int)_distanceBetween( current_node_coord, (*y_node_coord) );

				//Add to open list if not already there.
				if( !_isCoordInOpenList( (*y_node_coord) ))
				{
					_vOpenList.push_back( (*y_node_coord) );
					tentative_is_better = true;
				}
				//Check if the new tentative g score is better than the old
				else if( tentative__rgGScore < _rgGScore[y_node_coord->x][y_node_coord->y] )
					tentative_is_better = true;
				else
					tentative_is_better = false;

				//Update scores if necessary
				if( tentative_is_better )
				{
					_prgPathMap[y_node_coord->x][y_node_coord->y]->set_parent( _prgPathMap[current_node_coord.x][current_node_coord.y] );
					_rgGScore[y_node_coord->x][y_node_coord->y] = tentative__rgGScore;
					_rgHScore[y_node_coord->x][y_node_coord->y] = _heuristicEstimateOfDistance( (*y_node_coord), goal_pos );
					_rgFScore[y_node_coord->x][y_node_coord->y] = 
						_rgGScore[y_node_coord->x][y_node_coord->y] + 
						_rgHScore[y_node_coord->x][y_node_coord->y];
				}
			}
		}
	}
	_reconstuctPath(current_node_coord);

	Uint32 tmp_time;
	tmp_time = SDL_GetTicks() - _nStartTime;

	std::cout << "New path found.\n";
	std::cout << "Time to calctulate the new path: " << tmp_time << " milliseconds\n\n";
	return _vCompletePath;
}

int cAStar::_heuristicEstimateOfDistance ( cPosition start, cPosition goal)
{
	//Calculate manhattan distance
	return abs(start.x - goal.x + start.y - goal.y);
}

double cAStar::_distanceBetween (cPosition coord_1, cPosition coord_2 )
{
	//Calculate the "real" distance. 10 if side by side, 14 if diagonal
	if( coord_1.x == coord_2.x)
		return floor( 10 * abs( (double)coord_1.y - coord_2.y ) );
	else if( coord_1.y == coord_2.y)
		return floor( 10 * abs( (double)coord_1.x- coord_2.x) );
	else
		return floor( 10 * abs( sqrt( pow((double)coord_1.x - coord_2.x, 2) + pow((double)coord_1.y - coord_2.y, 2))));
}

cPosition cAStar::_getLowestFInOpenList()
{
	cPosition lowest_f = _vOpenList[0];

	for(std::vector<cPosition>::const_iterator it = _vOpenList.begin(); it != _vOpenList.end(); ++it)
	{
		if( _rgFScore[(*it).x][(*it).y] <
			_rgFScore[lowest_f.x][lowest_f.y] )
			lowest_f = (*it);
	}
	return lowest_f;
}

bool cAStar::_isCoordInCompletePath( cPosition coord )
{
	for(std::vector<cPosition>::const_iterator it = _vCompletePath.begin(); it != _vCompletePath.end(); ++it)
		if( *it == coord )
			return true;

	return false;
}
bool cAStar::_isCoordInOpenList( cPosition coord )
{
	for(std::vector<cPosition>::const_iterator it = _vOpenList.begin(); it != _vOpenList.end(); ++it)
		if( (*it) == coord )
			return true;

	return false;
}
bool cAStar::_isCoordInClosedList( cPosition coord )
{
	for(std::vector<cPosition>::const_iterator it = _vClosedList.begin(); it != _vClosedList.end(); ++it)
		if( (*it) == coord )
			return true;

	return false;
}

void cAStar::_reconstuctPath(cPosition goalNode)
{
	//Build a list (complete_path) by taking the parent of goal and follow the linked list through the parentnode
	_vCompletePath.clear();
	bool found_start = false;
	cPosition tmp_coord = _posGoal;
	while( !found_start && _prgPathMap[tmp_coord.x][tmp_coord.y]->get_parent() != NULL)
	{
		if( tmp_coord.x == _posStart.x && 
			tmp_coord.y == _posStart.y )
		{
			found_start = true;
			break;
		}

		_vCompletePath.push_back(tmp_coord);
		tmp_coord = _prgPathMap[tmp_coord.x][tmp_coord.y]->get_parent()->get_coordinate();
	}
}

std::vector<cPosition> cAStar::_getNeighbors(cPosition coordinate)
{
	std::vector<cPosition> tmp_list;
	cAStarNode* tmp_node;

	//Check diagonals
	if(coordinate.x > 0 && coordinate.y > 0)
	{
		tmp_node = _prgPathMap[coordinate.x-1][coordinate.y-1];
		if( tmp_node != NULL && 
			tmp_node->is_walkable() && 
			_prgPathMap[coordinate.x][coordinate.y-1]->is_walkable() && 
			_prgPathMap[coordinate.x-1][coordinate.y]->is_walkable()
			)
			tmp_list.push_back(tmp_node->get_coordinate());
	}

	if(coordinate.x < MAP_COLS-1 && coordinate.y > 0)
	{
		tmp_node = _prgPathMap[coordinate.x+1][coordinate.y-1];
		if( tmp_node != NULL && 
			tmp_node->is_walkable() &&
			_prgPathMap[coordinate.x][coordinate.y-1]->is_walkable() &&
			_prgPathMap[coordinate.x+1][coordinate.y]->is_walkable()
			)
			tmp_list.push_back(tmp_node->get_coordinate());
	}

	if(coordinate.x < MAP_COLS-1 && coordinate.y < MAP_ROWS-1)
	{
		tmp_node = _prgPathMap[coordinate.x+1][coordinate.y+1];
		if( tmp_node != NULL && 
			tmp_node->is_walkable() &&
			_prgPathMap[coordinate.x][coordinate.y+1]->is_walkable() &&
			_prgPathMap[coordinate.x+1][coordinate.y]->is_walkable()
			)
			tmp_list.push_back(tmp_node->get_coordinate());
	}

	if(coordinate.x > 0 && coordinate.y < MAP_ROWS-1)
	{
		tmp_node = _prgPathMap[coordinate.x-1][coordinate.y+1];
		if( tmp_node != NULL && 
			tmp_node->is_walkable() &&
			_prgPathMap[coordinate.x][coordinate.y+1]->is_walkable() &&
			_prgPathMap[coordinate.x-1][coordinate.y]->is_walkable()
			)
			tmp_list.push_back(tmp_node->get_coordinate());
	}



	//Check top, right, down and left
	if(coordinate.y > 0)
	{
		tmp_node = _prgPathMap[coordinate.x][coordinate.y-1];
		if( tmp_node != NULL && 
			tmp_node->is_walkable()
			)
			tmp_list.push_back(tmp_node->get_coordinate());
	}

	if(coordinate.x < MAP_COLS-1)
	{
		tmp_node = _prgPathMap[coordinate.x+1][coordinate.y];
		if( tmp_node != NULL && 
			tmp_node->is_walkable()
			)
			tmp_list.push_back(tmp_node->get_coordinate());
	}

	if(coordinate.y < MAP_ROWS-1)
	{
		tmp_node = _prgPathMap[coordinate.x][coordinate.y+1];
		if( tmp_node != NULL && 
			tmp_node->is_walkable()
			)
			tmp_list.push_back(tmp_node->get_coordinate());
	}

	if(coordinate.x > 0)
	{
		tmp_node = _prgPathMap[coordinate.x-1][coordinate.y];
		if( tmp_node != NULL && 
			tmp_node->is_walkable()
			)
			tmp_list.push_back(tmp_node->get_coordinate());
	}

	return tmp_list;
}