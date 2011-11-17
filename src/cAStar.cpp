#include "cAStar.h"

cAStar::cAStar( std::vector< std::vector<int> > map, std::vector<irr::core::vector2d<irr::s32>> units_list )
{
	std::vector<int> tmp;
	for( unsigned int col = 0; col < map.size(); ++col )
		for( unsigned int row = 0; row < map[0].size(); ++row )
		{
			_prgPathMap[col][row] = new cAStarNode( 
				irr::core::vector2d<irr::s32>(col, row), 
				map[col][row] == cMap::WALKABLE ); 
		}

		_prgPathMap[units_list[0].X][units_list[0].Y]->set_walkable( false );
		//_prgPathMap[units_list[1].X][units_list[1].Y]->set_walkable( false );
}

std::vector<irr::core::vector2d<irr::s32>> cAStar::GetBestPath( irr::core::vector2d<irr::s32> start_pos, irr::core::vector2d<irr::s32> goal_pos )
{	
	//std::cout << "Calculating new path to " << start_pos << " using A*\n";

	_posStart = start_pos;
	_posGoal = goal_pos;
	_vOpenList.push_back( start_pos );

	_rgGScore[start_pos.X][start_pos.Y] = 0;
	_rgHScore[start_pos.X][start_pos.Y] = _heuristicEstimateOfDistance( start_pos, goal_pos );
	_rgFScore[start_pos.X][start_pos.Y] = _rgHScore[start_pos.X][start_pos.Y];

	irr::core::vector2d<irr::s32> current_node_coord;
	std::vector<irr::core::vector2d<irr::s32>> neighbor_list;
	bool tentative_is_better;

	irr::core::vector2d<irr::s32> y_node_coord;

	while (!_vOpenList.empty())
	{
		//Get the "best" node from open_list
		current_node_coord = _getLowestFInOpenList();

		if( current_node_coord.X == goal_pos.X &&
			current_node_coord.Y == goal_pos.Y)
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
		for(std::vector<irr::core::vector2d<irr::s32>>::const_iterator y_node_coord = neighbor_list.begin(); y_node_coord != neighbor_list.end(); ++y_node_coord )
		{
			if( !_isCoordInClosedList( (*y_node_coord) ) )
			{
				//Get tentative g score
				int tentative__rgGScore = 
					_rgGScore[current_node_coord.X][current_node_coord.Y] + 
					(int)_distanceBetween( current_node_coord, (*y_node_coord) );

				//Add to open list if not already there.
				if( !_isCoordInOpenList( (*y_node_coord) ))
				{
					_vOpenList.push_back( (*y_node_coord) );
					tentative_is_better = true;
				}
				//Check if the new tentative g score is better than the old
				else if( tentative__rgGScore < _rgGScore[y_node_coord->X][y_node_coord->Y] )
					tentative_is_better = true;
				else
					tentative_is_better = false;

				//Update scores if necessary
				if( tentative_is_better )
				{
					_prgPathMap[y_node_coord->X][y_node_coord->Y]->set_parent( _prgPathMap[current_node_coord.X][current_node_coord.Y] );
					_rgGScore[y_node_coord->X][y_node_coord->Y] = tentative__rgGScore;
					_rgHScore[y_node_coord->X][y_node_coord->Y] = _heuristicEstimateOfDistance( (*y_node_coord), goal_pos );
					_rgFScore[y_node_coord->X][y_node_coord->Y] = 
						_rgGScore[y_node_coord->X][y_node_coord->Y] + 
						_rgHScore[y_node_coord->X][y_node_coord->Y];
				}
			}
		}
	}
	_reconstuctPath(current_node_coord);

	std::cout << "New path found.\n";
	return _vCompletePath;
}

int cAStar::_heuristicEstimateOfDistance ( irr::core::vector2d<irr::s32> start, irr::core::vector2d<irr::s32> goal)
{
	//Calculate manhattan distance
	return abs(start.X - goal.X + start.Y - goal.Y);
}

double cAStar::_distanceBetween (irr::core::vector2d<irr::s32> coord_1, irr::core::vector2d<irr::s32> coord_2 )
{
	//Calculate the "real" distance. 10 if side by side, 14 if diagonal
	if( coord_1.X == coord_2.X)
		return floor( 10 * abs( (double)coord_1.Y - coord_2.Y ) );
	else if( coord_1.Y == coord_2.Y)
		return floor( 10 * abs( (double)coord_1.X- coord_2.X) );
	else
		return floor( 10 * abs( sqrt( pow((double)coord_1.X - coord_2.X, 2) + pow((double)coord_1.Y - coord_2.Y, 2))));
}

irr::core::vector2d<irr::s32> cAStar::_getLowestFInOpenList()
{
	irr::core::vector2d<irr::s32> lowest_f = _vOpenList[0];

	for(std::vector<irr::core::vector2d<irr::s32>>::const_iterator it = _vOpenList.begin(); it != _vOpenList.end(); ++it)
	{
		if( _rgFScore[(*it).X][(*it).Y] <
			_rgFScore[lowest_f.X][lowest_f.Y] )
			lowest_f = (*it);
	}
	return lowest_f;
}

bool cAStar::_isCoordInCompletePath( irr::core::vector2d<irr::s32> coord )
{
	for(std::vector<irr::core::vector2d<irr::s32>>::const_iterator it = _vCompletePath.begin(); it != _vCompletePath.end(); ++it)
		if( *it == coord )
			return true;

	return false;
}
bool cAStar::_isCoordInOpenList( irr::core::vector2d<irr::s32> coord )
{
	for(std::vector<irr::core::vector2d<irr::s32>>::const_iterator it = _vOpenList.begin(); it != _vOpenList.end(); ++it)
		if( (*it) == coord )
			return true;

	return false;
}
bool cAStar::_isCoordInClosedList( irr::core::vector2d<irr::s32> coord )
{
	for(std::vector<irr::core::vector2d<irr::s32>>::const_iterator it = _vClosedList.begin(); it != _vClosedList.end(); ++it)
		if( (*it) == coord )
			return true;

	return false;
}

void cAStar::_reconstuctPath(irr::core::vector2d<irr::s32> goalNode)
{
	//Build a list (complete_path) by taking the parent of goal and follow the linked list through the parentnode
	_vCompletePath.clear();
	bool found_start = false;
	irr::core::vector2d<irr::s32> tmp_coord = _posGoal;
	while( !found_start && _prgPathMap[tmp_coord.X][tmp_coord.Y]->get_parent() != NULL)
	{
		if( tmp_coord.X == _posStart.X && 
			tmp_coord.Y == _posStart.Y )
		{
			found_start = true;
			break;
		}

		_vCompletePath.push_back(tmp_coord);
		cAStarNode *tmpNode = _prgPathMap[tmp_coord.X][tmp_coord.Y]->get_parent();
		if( tmpNode == NULL )
			std::cout << "ERROR: Cannot go there./n" ;
		else
			tmp_coord = tmpNode->get_coordinate();
	}
}

std::vector<irr::core::vector2d<irr::s32>> cAStar::_getNeighbors(irr::core::vector2d<irr::s32> coordinate)
{
	std::vector<irr::core::vector2d<irr::s32>> tmp_list;
	cAStarNode* tmp_node;

	//Check diagonals
	if(coordinate.X > 0 && coordinate.Y > 0)
	{
		tmp_node = _prgPathMap[coordinate.X-1][coordinate.Y-1];
		if( tmp_node != NULL && 
			tmp_node->is_walkable() && 
			_prgPathMap[coordinate.X][coordinate.Y-1]->is_walkable() && 
			_prgPathMap[coordinate.X-1][coordinate.Y]->is_walkable()
			)
			tmp_list.push_back(tmp_node->get_coordinate());
	}

	if(coordinate.X < MAP_COLS-1 && coordinate.Y > 0)
	{
		tmp_node = _prgPathMap[coordinate.X+1][coordinate.Y-1];
		if( tmp_node != NULL && 
			tmp_node->is_walkable() &&
			_prgPathMap[coordinate.X][coordinate.Y-1]->is_walkable() &&
			_prgPathMap[coordinate.X+1][coordinate.Y]->is_walkable()
			)
			tmp_list.push_back(tmp_node->get_coordinate());
	}

	if(coordinate.X < MAP_COLS-1 && coordinate.Y < MAP_ROWS-1)
	{
		tmp_node = _prgPathMap[coordinate.X+1][coordinate.Y+1];
		if( tmp_node != NULL && 
			tmp_node->is_walkable() &&
			_prgPathMap[coordinate.X][coordinate.Y+1]->is_walkable() &&
			_prgPathMap[coordinate.X+1][coordinate.Y]->is_walkable()
			)
			tmp_list.push_back(tmp_node->get_coordinate());
	}

	if(coordinate.X > 0 && coordinate.Y < MAP_ROWS-1)
	{
		tmp_node = _prgPathMap[coordinate.X-1][coordinate.Y+1];
		if( tmp_node != NULL && 
			tmp_node->is_walkable() &&
			_prgPathMap[coordinate.X][coordinate.Y+1]->is_walkable() &&
			_prgPathMap[coordinate.X-1][coordinate.Y]->is_walkable()
			)
			tmp_list.push_back(tmp_node->get_coordinate());
	}



	//Check top, right, down and left
	if(coordinate.Y > 0)
	{
		tmp_node = _prgPathMap[coordinate.X][coordinate.Y-1];
		if( tmp_node != NULL && 
			tmp_node->is_walkable()
			)
			tmp_list.push_back(tmp_node->get_coordinate());
	}

	if(coordinate.X < MAP_COLS-1)
	{
		tmp_node = _prgPathMap[coordinate.X+1][coordinate.Y];
		if( tmp_node != NULL && 
			tmp_node->is_walkable()
			)
			tmp_list.push_back(tmp_node->get_coordinate());
	}

	if(coordinate.Y < MAP_ROWS-1)
	{
		tmp_node = _prgPathMap[coordinate.X][coordinate.Y+1];
		if( tmp_node != NULL && 
			tmp_node->is_walkable()
			)
			tmp_list.push_back(tmp_node->get_coordinate());
	}

	if(coordinate.X > 0)
	{
		tmp_node = _prgPathMap[coordinate.X-1][coordinate.Y];
		if( tmp_node != NULL && 
			tmp_node->is_walkable()
			)
			tmp_list.push_back(tmp_node->get_coordinate());
	}

	return tmp_list;
}