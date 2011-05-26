#include "a_star.h"

AStar::AStar( std::vector< std::vector<int> > map, std::vector<Position> units_list )
{
	std::vector<int> tmp;
	for( unsigned int col = 0; col < map.size(); ++col )
		for( unsigned int row = 0; row < map[0].size(); ++row )
		{
			path_map[col][row] = new AStarNode( 
				Position(col, row), 
				map[col][row] == Map::WALKABLE );
		}

		path_map[units_list[0].x][units_list[0].y]->set_walkable( false );
		//path_map[units_list[1].x][units_list[1].y]->set_walkable( false );
}

std::vector<Position> AStar::get_best_path( Position start_pos, Position goal_pos )
{
	std::cout << "Calculating new path using A*\n";

	_start_pos = start_pos;
	_goal_pos = goal_pos;
	open_list.push_back( start_pos );

	g_score[start_pos.x][start_pos.y] = 0;
	h_score[start_pos.x][start_pos.y] = heuristic_estimate_of_distance( start_pos, goal_pos );
	f_score[start_pos.x][start_pos.y] = h_score[start_pos.x][start_pos.y];

	Position current_node_coord;
	std::vector<Position> neighbor_list;
	bool tentative_is_better;

	Position y_node_coord;

	while (!open_list.empty())
	{
		//Get the "best" node from open_list
		current_node_coord = get_lowest_f_in_open_list();

		if( current_node_coord.x == goal_pos.x &&
			current_node_coord.y == goal_pos.y)
		{
			reconstuct_path(current_node_coord);
			break;
		}

		//Add to closed_list
		closed_list.push_back(current_node_coord);

		//Remove from open_list
		int tmpPos;
		for ( unsigned int i = 0; i < open_list.size(); ++i)
		{
			if(open_list[i] == current_node_coord)
			{
				tmpPos = i;
				i = open_list.size();
			}
		}
		open_list.erase(open_list.begin() + tmpPos);
		neighbor_list = get_neighbors( current_node_coord );

		//Process all neighbors
		for(std::vector<Position>::const_iterator y_node_coord = neighbor_list.begin(); y_node_coord != neighbor_list.end(); ++y_node_coord )
		{
			if( !is_coord_in_closed_list( (*y_node_coord) ) )
			{
				//Get tentative g score
				int tentative_g_score = 
					g_score[current_node_coord.x][current_node_coord.y] + 
					(int)distance_between( current_node_coord, (*y_node_coord) );

				//Add to open list if not already there.
				if( !is_coord_in_open_list( (*y_node_coord) ))
				{
					open_list.push_back( (*y_node_coord) );
					tentative_is_better = true;
				}
				//Check if the new tentative g score is better than the old
				else if( tentative_g_score < g_score[y_node_coord->x][y_node_coord->y] )
					tentative_is_better = true;
				else
					tentative_is_better = false;

				//Update scores if necessary
				if( tentative_is_better )
				{
					path_map[y_node_coord->x][y_node_coord->y]->set_parent( path_map[current_node_coord.x][current_node_coord.y] );
					g_score[y_node_coord->x][y_node_coord->y] = tentative_g_score;
					h_score[y_node_coord->x][y_node_coord->y] = heuristic_estimate_of_distance( (*y_node_coord), goal_pos );
					f_score[y_node_coord->x][y_node_coord->y] = 
						g_score[y_node_coord->x][y_node_coord->y] + 
						h_score[y_node_coord->x][y_node_coord->y];
				}
			}
		}
	}
	reconstuct_path(current_node_coord);

	std::cout << "New path found.\n";
	return complete_path;
}

int AStar::heuristic_estimate_of_distance (Position start, Position goal)
{
	//Calculate manhattan distance
	return abs(start.x - goal.x + start.y - goal.y);
}

double AStar::distance_between (Position coord_1, Position coord_2 )
{
	//Calculate the "real" distance. 10 if side by side, 14 if diagonal
	if( coord_1.x == coord_2.x)
		return floor( 10 * abs( (double)coord_1.y - coord_2.y ) );
	else if( coord_1.y == coord_2.y)
		return floor( 10 * abs( (double)coord_1.x- coord_2.x) );
	else
		return floor( 10 * abs( sqrt( pow((double)coord_1.x - coord_2.x, 2) + pow((double)coord_1.y - coord_2.y, 2))));
}

Position AStar::get_lowest_f_in_open_list()
{
	Position lowest_f = open_list[0];

	for(std::vector<Position>::const_iterator it = open_list.begin(); it != open_list.end(); ++it)
	{
		if( f_score[(*it).x][(*it).y] <
			f_score[lowest_f.x][lowest_f.y] )
			lowest_f = (*it);
	}
	return lowest_f;
}

bool AStar::is_coord_in_complete_path( Position coord )
{
	for(std::vector<Position>::const_iterator it = complete_path.begin(); it != complete_path.end(); ++it)
		if( *it == coord )
			return true;

	return false;
}
bool AStar::is_coord_in_open_list( Position coord )
{
	for(std::vector<Position>::const_iterator it = open_list.begin(); it != open_list.end(); ++it)
		if( (*it) == coord )
			return true;

	return false;
}
bool AStar::is_coord_in_closed_list( Position coord )
{
	for(std::vector<Position>::const_iterator it = closed_list.begin(); it != closed_list.end(); ++it)
		if( (*it) == coord )
			return true;

	return false;
}

void AStar::reconstuct_path(Position goalNode)
{
	//Build a list (complete_path) by taking the parent of goal and follow the linked list through the parentnode
	complete_path.clear();
	bool found_start = false;
	Position tmp_coord = _goal_pos;
	while( !found_start && path_map[tmp_coord.x][tmp_coord.y]->get_parent() != NULL)
	{
		if( tmp_coord.x == _start_pos.x && 
			tmp_coord.y == _start_pos.y )
		{
			found_start = true;
			break;
		}

		complete_path.push_back(tmp_coord);
		tmp_coord = path_map[tmp_coord.x][tmp_coord.y]->get_parent()->get_coordinate();
	}
}

std::vector<Position> AStar::get_neighbors(Position coordinate)
{
	std::vector<Position> tmp_list;
	AStarNode* tmp_node;

	//Check diagonals
	if(coordinate.x > 0 && coordinate.y > 0)
	{
		tmp_node = path_map[coordinate.x-1][coordinate.y-1];
		if( tmp_node != NULL && 
			tmp_node->is_walkable() && 
			path_map[coordinate.x][coordinate.y-1]->is_walkable() && 
			path_map[coordinate.x-1][coordinate.y]->is_walkable()
			)
			tmp_list.push_back(tmp_node->get_coordinate());
	}

	if(coordinate.x < MAP_COLS-1 && coordinate.y > 0)
	{
		tmp_node = path_map[coordinate.x+1][coordinate.y-1];
		if( tmp_node != NULL && 
			tmp_node->is_walkable() &&
			path_map[coordinate.x][coordinate.y-1]->is_walkable() &&
			path_map[coordinate.x+1][coordinate.y]->is_walkable()
			)
			tmp_list.push_back(tmp_node->get_coordinate());
	}

	if(coordinate.x < MAP_COLS-1 && coordinate.y < MAP_ROWS-1)
	{
		tmp_node = path_map[coordinate.x+1][coordinate.y+1];
		if( tmp_node != NULL && 
			tmp_node->is_walkable() &&
			path_map[coordinate.x][coordinate.y+1]->is_walkable() &&
			path_map[coordinate.x+1][coordinate.y]->is_walkable()
			)
			tmp_list.push_back(tmp_node->get_coordinate());
	}

	if(coordinate.x > 0 && coordinate.y < MAP_ROWS-1)
	{
		tmp_node = path_map[coordinate.x-1][coordinate.y+1];
		if( tmp_node != NULL && 
			tmp_node->is_walkable() &&
			path_map[coordinate.x][coordinate.y+1]->is_walkable() &&
			path_map[coordinate.x-1][coordinate.y]->is_walkable()
			)
			tmp_list.push_back(tmp_node->get_coordinate());
	}



	//Check top, right, down and left
	if(coordinate.y > 0)
	{
		tmp_node = path_map[coordinate.x][coordinate.y-1];
		if( tmp_node != NULL && 
			tmp_node->is_walkable()
			)
			tmp_list.push_back(tmp_node->get_coordinate());
	}

	if(coordinate.x < MAP_COLS-1)
	{
		tmp_node = path_map[coordinate.x+1][coordinate.y];
		if( tmp_node != NULL && 
			tmp_node->is_walkable()
			)
			tmp_list.push_back(tmp_node->get_coordinate());
	}

	if(coordinate.y < MAP_ROWS-1)
	{
		tmp_node = path_map[coordinate.x][coordinate.y+1];
		if( tmp_node != NULL && 
			tmp_node->is_walkable()
			)
			tmp_list.push_back(tmp_node->get_coordinate());
	}

	if(coordinate.x > 0)
	{
		tmp_node = path_map[coordinate.x-1][coordinate.y];
		if( tmp_node != NULL && 
			tmp_node->is_walkable()
			)
			tmp_list.push_back(tmp_node->get_coordinate());
	}

	return tmp_list;
}