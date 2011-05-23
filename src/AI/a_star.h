#pragma once

#include "Math.h"
#include "../helpers/position.h"
#include "a_star_node.h"
#include "../map/map.h"

class AStar
{
private:
	int g_score[MAP_COLS][MAP_ROWS];
	int h_score[MAP_COLS][MAP_ROWS];
	int f_score[MAP_COLS][MAP_ROWS];

	AStarNode* path_map[MAP_COLS][MAP_ROWS];

	std::vector<Position> closed_list;
	std::vector<Position> open_list;
	std::vector<Position> complete_path;

	Position _start_pos;
	Position _goal_pos;


	int heuristic_estimate_of_distance (Position start, Position goal);
	int distance_between (Position coord_1, Position coord_2 );
	Position get_lowest_f_in_open_list();
	bool is_coord_in_complete_path( Position coord );
	bool is_coord_in_open_list( Position coord );
	bool is_coord_in_closed_list( Position coord );
	void reconstuct_path(Position goalNode);
	std::vector<Position> get_neighbors(Position coordinate);

public:
	AStar( std::vector< std::vector<int> > map);
	std::vector<Position> get_best_path( Position start_pos, Position goal_pos );
};