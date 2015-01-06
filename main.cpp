#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "options.h"
#include "maze.h"
#include "depthBuilder.h"
#include "mazeFactory.h"
#include "disjointSets.h"

#define UNUSED(x) (void)(x)

static bool loadBinary(Maze *maze, Option *option) {
  maze->clear();
  return maze->load(option->getValue(0));
}

static bool saveBinary(Maze *maze, Option *option) {
  return maze->save(option->getValue(0));
}

static bool saveSVG(Maze *maze, Option *option) {
  return maze->saveSVG(option->getValue(0));
}

static bool generateByRB(Maze *maze, Option *option) {
  maze->clear();
  try {
    return MazeFactory::getDepthBuilder().build(maze, 
        std::stoi(option->getValue(1)),
        std::stoi(option->getValue(2)), 
        std::stoi(option->getValue(0)));
  } catch (std::invalid_argument &e) {
    return false;
  }
}

static bool generateByKruskal(Maze *maze, Option *option) {
  maze->clear();
  try {
    return MazeFactory::getKruskalBuilder().build(maze,
        std::stoi(option->getValue(1)),
        std::stoi(option->getValue(2)),
        std::stoi(option->getValue(0)));
  } catch (std::invalid_argument &e) {
    return false;
  }
}

static bool solveByDfs(Maze *maze, Option *option) {
  UNUSED(option);
  return MazeFactory::getDfsMazeSolver().solve(maze);
}

static bool solveByBfs(Maze *maze, Option *option) {
  UNUSED(option);
  return MazeFactory::getBfsMazeSolver().solve(maze);
}

static bool solveByAstar(Maze *maze, Option *option) {
  UNUSED(option);
  return MazeFactory::getAstarMazeSolver().solve(maze);
}

int main(int argc, char **argv) {
  Maze maze;

  // Expected options that the program can handle. Can be improved for assignment 2.
  auto options = OptionSet({
      {"--lb", "Loading maze: `0`\n", "Failed to load maze: `0`\n", &loadBinary, "Load Binary file: filename.maze"},
      {"--sb", "Saving binary maze: `0`\n", "Failed to save binary maze: `0`\n", &saveBinary, "Save Binary file: filename.maze"},
      {"--sv", "Saving svg maze: `0`\n", "Failed to save svg maze: `0`\n", &saveSVG, "Save SVG file: filename.svg"},
      {"--pd", "Solving maze\n", "Failed to solve the maze\n", &solveByDfs, "Solve the maze using depth first search", 0},
      {"--pb", "Solving maze\n", "Failed to solve the maze\n", &solveByBfs, "Solve the maze using breadth first search", 0},
      {"--pa", "Solving maze\n", "Failed to solve the maze\n", &solveByAstar, "Solve the maze using a* search", 0},
      {"-gr", "Generating maze with seed: `0`, width: `1`, height: `2`\n", "Failed to build maze", &generateByRB,
          "Generate maze using the recursive backtracking algorithm: seed width height\n", 3},
      {"-gk", "Generating maze with seed: `0`, width: `1`, height: `2`\n", "Failed to build maze\n", &generateByKruskal,
          "Generate maze using kruskal’s algorithm: seed width height", 3}
  });

  if (!options.parse(argc, argv))
    options.printUsage();
  else
    options.run(&maze);

  return EXIT_SUCCESS;
}
