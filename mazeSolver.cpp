#include "mazeSolver.h"
#include "maze.h"

///
/// Builds the grid of visitFlags matching the grid in the maze. Also builds 
//  the unvisited set.
/// @param maze the maze being solved.
///
void MazeSolver::buildVisitFlags(Maze *maze) {
  auto &cells = maze->getCells();
  visitFlags.resize(cells.size());
  for (int i = 0; i < (int) cells.size(); i++) {
    visitFlags[i].resize(cells[i].size(), false);
  }
}
