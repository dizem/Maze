#include "bfsMazeSolver.h"
#include "maze.h"
#include <queue>

///
/// Searches for path in the maze and sets the path to the maze if found.
/// @param maze the maze being solved.
/// @return true if the maze is solved, or false otherwise.
///
bool BfsMazeSolver::solve(Maze *maze) {
  // Initialize the visit flags
  buildVisitFlags(maze);
  // The nodes to be de-allocated.
  std::vector<Node *> allocated;
  //  Queue for BFS.
  std::queue<Node *> queue;

  Node *node, *top = nullptr;
  bool found = false;

  // Push the start cell to the queue.
  allocated.push_back(node = new Node(&maze->getCells()[0][0]));
  queue.push(node);

  // While the queue is not empty
  while (!queue.empty()) {
    // Pop a node from the queue.
    top = queue.front();
    queue.pop();
    
    // Mark it as visited.
    visitFlags[top->cell->x][top->cell->y] = true;
    
    // If it is the destination, break.
    if (top->cell->x == maze->getHeight() - 1 
        && top->cell->y == maze->getWidth() - 1) {
      found = true;
      break;
    }
    
    // For each unvisited neighbour cell of the current cell,
    for (auto neighbour : top->cell->adjacents) {
      if (!visitFlags[neighbour->x][neighbour->y]) {
        // Push it to the queue.
        allocated.push_back(node = new Node(neighbour, top));
        queue.push(node);
      }
    }
  }
  
  // Build the path.
  if (found) {
    std::vector<Cell> path;
    while (top) {
      path.push_back(*top->cell);
      top = top->prev;
    }
    maze->setPath(path);
  }

  // De-allocate the nodes.
  for (auto ptr : allocated) {
    delete ptr;
  }
  return found;
}
