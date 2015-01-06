#include <iostream>
#include "dfsMazeSolver.h"
#include "maze.h"

///
/// Searches for the path recursively.
/// @param maze the maze being solved.
/// @param current the current cell being traversing.
/// @param path the current searching path.
/// @return true if the maze is solved, or false otherwise.
///
bool DfsMazeSolver::search(Maze *maze, Cell *current, std::vector<Cell> &path) {
  // If the destination is reached, return true.
  if (current->x == maze->getHeight() - 1
      && current->y == maze->getWidth() - 1) {
    return true;
  }
  
  // Loop for each unvisited neighbour of the current node,
  for (auto neighbour : current->adjacents) {
    if (!visitFlags[neighbour->x][neighbour->y]) {
      // Mark it as visited
      visitFlags[current->x][current->y] = true;
      // Add it to the path.
      path.push_back(*neighbour);
      // Recur to search in the neighbour node
      if (search(maze, neighbour, path)) {
        // If solved, return true.
        return true;
      }
      // Remove the neighbour node from the path.
      path.pop_back();
    }
  }
  // Not found.
  return false;
}

///
/// Searches for path in the maze and sets the path to the maze if found.
/// @param maze the maze being solved.
/// @return true if the maze is solved, or false otherwise.
///
bool DfsMazeSolver::solve(Maze *maze) {
  // Build the visit flags.
  buildVisitFlags(maze);
  
  // A vector to hold the path.
  std::vector<Cell> path;
  
  // Mark the start cell as visited, and add it to the path.
  Cell *start = &maze->getCells()[0][0];
  visitFlags[start->x][start->y] = true;
  path.push_back(*start);
  
  // Search recursively,
  if (search(maze, start, path)) {
    // If a path is found, set it to the maze.
    maze->setPath(path);
    return true;
    
  } else {
    // Not found.
    return false;
  }
}
