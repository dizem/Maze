#pragma once

#include <stack>
#include <set>
#include <vector>
#include <random>
#include "singletonBase.h"
#include "MazeBuilder.h"

struct Cell;
class Maze;

///
/// Builds mazes using Recursive Backtracking for Depth First Search, 
/// more details available at:
/// http://en.wikipedia.org/wiki/Maze_generation_algorithm#Recursive_backtracker
///
class DepthBuilder : public MazeBuilder, public SingletonBase<DepthBuilder>
{
  friend class SingletonBase<DepthBuilder>;
private:
  DepthBuilder() {}
  ~DepthBuilder() {}
  
  ///< Cells that are currently being visited by the algorithm, used for 
  /// backtracking.
	std::stack<Cell*> visited;
  ///< Flags for visited/unvisited, matching every cell in the maze.
	std::vector<std::vector<bool>> visitFlags;		

private:
	///
	/// Builds the grid of visitFlags matching the grid in the maze. Also builds 
	/// the unvisited set.
	/// @param maze the maze being populated.
	///
	void buildVisitFlags(Maze *maze);
	
	///
	/// Visits a cell, marking it as visited and removing it from the unvisited 
	/// set.
	/// @param cell the cell being visited.
	/// @return the cell being visited.
	///
	Cell *visit(Cell *cell);

	///
	/// Retreives a random unvisited neighbour cell.
	/// @param maze the maze being populated.
	/// @param cell the cell of which a neighbour is being randomly retrieved.
	/// @param rng the random number generator used to select a neighbouring cell.
	/// @return the cell that has been chosen, or nullptr if none exist.
	///
	Cell *getUnvisitedNeighbour(Maze *maze, Cell *cell, std::mt19937 &rng);

public:
	///
	/// Populates the maze with appropriate edge/adjacency list data using the 
	/// recursive backtracking algorithm, resets width/height of the maze.
	/// @param maze the maze being populated.
	/// @param width the desired width of the maze.
	/// @param height the desired height of the maze.
	/// @param seed the value used to seed the random number generator.
	/// @return false if invalid width/height is given, otherwise true.
	///
	bool build(Maze *maze, int width, int height, int seed);
};
