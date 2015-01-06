#pragma once

#include "mazeSolver.h"
#include "singletonBase.h"

///
/// Solves mazes using breadth first search algorithm.
///
class BfsMazeSolver : public MazeSolver, public SingletonBase<BfsMazeSolver> {
  friend class SingletonBase<BfsMazeSolver>;
private:
  BfsMazeSolver() {}
  ~BfsMazeSolver() {}

  ///
  /// Node for searching.
  ///
  class Node {
  public:
    Cell *cell; /// Cell of the node.
    Node *prev; /// Previous node in the path.

    ///
    /// Constructor
    /// @param cell Cell of the node.
    /// @param prev Previous node in the path.
    ///
    Node(Cell *cell, Node *prev = nullptr) : cell(cell), prev(prev) {
    }
  };

public:
  ///
  /// Searches for path in the maze and sets the path to the maze if found.
  /// @param maze the maze being solved.
  /// @return true if the maze is solved, or false otherwise.
  ///
  bool solve(Maze *maze);
};
