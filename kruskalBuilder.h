#pragma once

#include <random>
#include "singletonBase.h"
#include "MazeBuilder.h"
#include "disjointSets.h"

class Maze;

///
/// Builds mazes using the Kruskal's algorithm
/// ref: http://en.wikipedia
/// .org/wiki/Maze_generation_algorithm#Randomized_Kruskal.27s_algorithm
///
class KruskalBuilder : public MazeBuilder, public SingletonBase<KruskalBuilder>
{
  friend class SingletonBase<KruskalBuilder>;
private:
  KruskalBuilder() {}
  ~KruskalBuilder() {}

public:
  ///
  /// Populates the maze with appropriate edge/adjacency list data,
  //        resets width/height of the maze.
  /// @param maze the maze being populated.
  /// @param width the desired width of the maze.
  /// @param height the desired height of the maze.
  /// @param seed the value used to seed the random number generator.
  /// @return false if invalid width/height is given, otherwise true.
  ///
  bool build(Maze *maze, int width, int height, int seed);
};
