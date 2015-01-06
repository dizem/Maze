#pragma once

#include "mazeBuilder.h"
#include "mazeSolver.h"

///
/// The factory class providing maze builders and maze solvers.
///
class MazeFactory {
private:
  /// The maze factory class can not be created and copied.
  MazeFactory() = delete;
  MazeFactory(const MazeFactory &) = delete;
  MazeFactory &operator=(const MazeFactory &) = delete;

public:
  ///
  /// @return the maze builder using the recursive depth algorithm.
  ///
  static MazeBuilder &getDepthBuilder();

  ///
  /// @return the maze builder using the Kruskal's algorithm.
  ///
  static MazeBuilder &getKruskalBuilder();

  ///
  /// @return the maze solver using the BFS algorithm.
  ///
  static MazeSolver &getBfsMazeSolver();

  ///
  /// @return the maze solver using the DFS algorithm.
  ///
  static MazeSolver &getDfsMazeSolver();

  ///
  /// @return the maze solver using the Astar algorithm.
  ///
  static MazeSolver &getAstarMazeSolver();
};
