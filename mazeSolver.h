#pragma once

#include <vector>

struct Cell;
class Maze;

///
/// Interface of the maze solvers.
///
class MazeSolver {
protected:
  ///< Flags for visited/unvisited, matching every cell in the maze.
  std::vector<std::vector<bool>> visitFlags;

  ///
  /// Builds the grid of visitFlags matching the grid in the maze. Also builds
  /// the unvisited set.
  /// @param maze the maze being solved.
  ///
  void buildVisitFlags(Maze *maze);

public:
  ///
  /// Searches for path in the maze and sets the path to the maze if found.
  /// @param maze the maze being solved.
  /// @return true if the maze is solved, or false otherwise.
  ///
  virtual bool solve(Maze *maze) = 0;
};
