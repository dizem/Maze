#pragma once

#include "mazeSolver.h"
#include "singletonBase.h"

///
/// Solves mazes using depth first search algorithm.
///
class DfsMazeSolver : public MazeSolver, public SingletonBase<DfsMazeSolver> {
  friend class SingletonBase<DfsMazeSolver>;
private:
  DfsMazeSolver() {}
  ~DfsMazeSolver() {}

  ///
  /// Searches for the path recursively.
  /// @param maze the maze being solved.
  /// @param current the current cell being traversing.
  /// @param path the current searching path.
  /// @return true if the maze is solved, or false otherwise.
  ///
  bool search(Maze *maze, Cell *current, std::vector<Cell> &path);

public:
  ///
  /// Searches for path in the maze and sets the path to the maze if found.
  /// @param maze the maze being solved.
  /// @return true if the maze is solved, or false otherwise.
  ///
  bool solve(Maze *maze);
};
