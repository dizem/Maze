#include <iostream>
#include "kruskalBuilder.h"
#include "maze.h"
#include <random>
#include <algorithm>

///
/// Populates the maze with appropriate edge/adjacency list data,
//        resets width/height of the maze.
/// @param maze the maze being populated.
/// @param width the desired width of the maze.
/// @param height the desired height of the maze.
/// @param seed the value used to seed the random number generator.
/// @return false if invalid width/height is given, otherwise true.
///
bool KruskalBuilder::build(Maze *maze, int width, int height, int seed) {
  // Set random seed.
  srand((unsigned int) seed);
  
  // If the size is invalid, return false.
  if (width <= 0 || height <= 0) {
    return false;
  }
  // Set size to the maze.
  maze->setSize(width, height);
  
  // Create a random number generator.
  std::mt19937 rng(seed);

  // Create a list of all walls
  std::vector<Edge> walls;
  for (int x = 0; x < height; ++x)
    for (int y = 0; y < width; ++y) {
      if (x != height - 1)
        walls.push_back(Edge{x, y, x + 1, y});
      if (y != width - 1)
        walls.push_back(Edge{x, y, x, y + 1});
    }

  // Create a set for each cell
  DisjointSets dsets(width * height + 1);

  // For each wall, in some random order:
  std::random_shuffle(walls.begin(), walls.end());
  for (auto wall : walls) {
    // If the cells divided by this wall belong to distinct sets:
    if (dsets.findSet(wall.index1x * maze->getWidth() + wall.index1y)
        != dsets.findSet(wall.index2x * maze->getWidth() + wall.index2y)) {
      // Join the sets of the formerly divided cells. 
      dsets.setUnion(wall.index1x * maze->getWidth() + wall.index1y,
          wall.index2x * maze->getWidth() + wall.index2y);
      // Remove the current wall. 
      maze->addEdge(wall.index1x, wall.index1y, wall.index2x, wall.index2y);
    }
  }
  return true;
}
