#pragma once

#include "mazeSolver.h"
#include "singletonBase.h"
#include "maze.h"

///
/// Solves mazes using the astar search algorithm.
///
class AstarMazeSolver
    : public MazeSolver, public SingletonBase<AstarMazeSolver> {
  friend class SingletonBase<AstarMazeSolver>;

private:
  AstarMazeSolver() {
  }

  ~AstarMazeSolver() {
  }

  std::vector<std::vector<bool>> inHeap; // whether (x,y) is in the heap or not.

  ///
  /// Node for searching.
  ///
  class Node {
  public:
    Cell *cell;       /// Cell of the node.
    Node *prev;       /// Previous node in the path.
    int pathLength;   /// Length of the current path.
    int distToDest;   /// The manhattan distance from the current cell to the 
                      /// destination.

    ///
    /// Constructor
    /// @param cell Cell of the node.
    /// @param prev Previous node in the path.
    /// @param pathLength Length of the current path.
    /// @param distToDest The manhattan distance from the current cell to the 
    ///                   destination.
    ///
    Node(Cell *cell, Node *prev = nullptr, 
        int pathLength = 0, int distToDest = 0)
        : cell(cell),
          prev(prev),
          pathLength(pathLength),
          distToDest(distToDest) {
    }

    ///
    /// @return the priority of the node which is the sum of the path length and 
    ///         the distance from the current cell to the destination. 
    ///
    int priority() const {
      return pathLength + distToDest;
    }
  };

  ///
  /// Returns true if the two nodes contains the same cell.
  /// @param the first node 
  /// @param the second node
  /// @return true if the two nodes contains the same cell, or false otherwise.
  ///
  static bool nodeEquals(Node *a, Node *b);

  ///
  /// Computes the manhattan distance between the two cells.
  /// @param the first cell
  /// @param the second cell
  /// @return the manhattan distance between the two cells.
  ///
  int distance(Cell &c1, Cell &c2) const;

public:
  ///
  /// Searches for path in the maze and sets the path to the maze if found.
  /// @param maze the maze being solved.
  /// @return true if the maze is solved, or false otherwise.
  ///
  bool solve(Maze *maze);
};
