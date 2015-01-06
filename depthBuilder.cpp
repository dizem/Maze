#include "depthBuilder.h"

#include "maze.h"

void DepthBuilder::buildVisitFlags(Maze *maze) {
  auto &cells = maze->getCells();
  visitFlags.resize(cells.size());
  for (int i = 0; i < (int) cells.size(); i++)
    visitFlags[i].resize(cells[i].size(), false);
}

Cell *DepthBuilder::visit(Cell *cell) {
  visitFlags[cell->x][cell->y] = true;
  return cell;
}

Cell *DepthBuilder::getUnvisitedNeighbour(
    Maze *maze, Cell *cell, std::mt19937 &rng) {
  // Get all unvisited neighbours of the current cell (max of 4).
  static std::vector<Cell *> neighbours(4);
  int size = 0;
  auto &cells = maze->getCells();

  if (cell->x > 0 && !visitFlags[cell->x - 1][cell->y])
    neighbours[size++] = &cells[cell->x - 1][cell->y];
  if (cell->y > 0 && !visitFlags[cell->x][cell->y - 1])
    neighbours[size++] = &cells[cell->x][cell->y - 1];
  if (cell->x < maze->getWidth() - 1 && !visitFlags[cell->x + 1][cell->y])
    neighbours[size++] = &cells[cell->x + 1][cell->y];
  if (cell->y < maze->getHeight() - 1 && !visitFlags[cell->x][cell->y + 1])
    neighbours[size++] = &cells[cell->x][cell->y + 1];

  // If there are no unvisited neighbours, then we're done here.
  if (size == 0)
    return nullptr;

  // Pick a random neighbour and return it.
  return neighbours[rng() % size];
}

bool DepthBuilder::build(Maze *maze, int width, int height, int seed) {
  if (width <= 0 || height <= 0)
    return false;

  maze->setSize(width, height);
  buildVisitFlags(maze);

  std::mt19937 rng(seed);
  auto &cells = maze->getCells();

  // Start at cell 0,0.
  auto *curr = visit(&cells[0][0]);

  for (int i = 0; i < width * height - 1;) {
    auto *chosen = getUnvisitedNeighbour(maze, curr, rng);
    if (chosen) {
      visited.push(curr);
      maze->addEdge(curr->x, curr->y, chosen->x, chosen->y);
      curr = visit(chosen);
      i++;
    }
    else {
      curr = visited.top();
      visited.pop();
    }
  }

  // Just in case.
  while (!visited.empty())
    visited.pop();
  visitFlags.clear();

  return true;
}
