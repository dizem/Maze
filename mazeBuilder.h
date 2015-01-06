#pragma once

class Maze;

///
/// Interface of the maze builders.
///
class MazeBuilder {
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
  virtual bool build(Maze *maze, int width, int height, int seed) = 0;
};

