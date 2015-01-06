#include "mazeFactory.h"
#include "dfsMazeSolver.h"
#include "bfsMazeSolver.h"
#include "astarMazeSolver.h"
#include "DepthBuilder.h"
#include "KruskalBuilder.h"

///
/// @return the maze builder using the recursive depth algorithm.
///
MazeBuilder &MazeFactory::getDepthBuilder() {
  return DepthBuilder::Instance();
}

///
/// @return the maze builder using the Kruskal's algorithm.
///
MazeBuilder &MazeFactory::getKruskalBuilder() {
  return KruskalBuilder::Instance();
}

///
/// @return the maze solver using the BFS algorithm.
///
MazeSolver &MazeFactory::getBfsMazeSolver() {
  return BfsMazeSolver::Instance();
}

///
/// @return the maze solver using the DFS algorithm.
///
MazeSolver &MazeFactory::getDfsMazeSolver() {
  return DfsMazeSolver::Instance();
}

///
/// @return the maze solver using the Astar algorithm.
///
MazeSolver &MazeFactory::getAstarMazeSolver() {
  return AstarMazeSolver::Instance();
}
