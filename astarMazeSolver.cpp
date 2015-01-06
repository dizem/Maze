#include "astarMazeSolver.h"
#include "binaryHeap.h"
#include <cstdlib>

///
/// Searches for path in the maze and sets the path to the maze if found.
/// @param maze the maze being solved.
/// @return true if the maze is solved, or false otherwise.
///
bool AstarMazeSolver::solve(Maze *maze) {
  // Initialize the visit flags.
  buildVisitFlags(maze);

  // Initialize the in-heap flags. 
  auto &cells = maze->getCells();
  inHeap.resize(cells.size());
  for (int i = 0; i < (int) cells.size(); i++)
    inHeap[i].resize(cells[i].size(), false);

  // Get the source and destination cells.
  Cell &begin = maze->getCells()[0][0];
  Cell &end = maze->getCells()[maze->getHeight() - 1][maze->getWidth() - 1];

  // Hold the nodes to be de-allocated.
  std::vector<Node *> allocated;

  // Binary heap for A*
  BinaryHeap<Node *> heap(&nodeEquals);

  Node *node, *top;

  // Push the source cell to the heap.
  node = new Node(&maze->getCells()[begin.x][begin.y], 0, distance(begin, end));
  allocated.push_back(node);
  heap.push(node, node->priority());
  inHeap[begin.x][begin.y] = true;

  bool found = false;
  // While the heap is not empty.
  while (!heap.empty()) {
    // Pop a node from the queue.
    top = heap.pop();
    inHeap[top->cell->x][top->cell->y] = false;

    // Mark it as visited.
    visitFlags[top->cell->x][top->cell->y] = true;

    // If it is the destionation node, break.
    if (top->cell->x == maze->getHeight() - 1 && top->cell->y == maze->getWidth() - 1) {
      found = true;
      break;
    }

    // Compute the length of path.
    int pathLength = top->pathLength + 1;

    // For each unvisited neighbour cell of the current cell,
    for (auto neighbour : top->cell->adjacents) {
      if (!visitFlags[neighbour->x][neighbour->y]) {

        // Compute the manhattan distance.
        int distToDest = distance(*neighbour, end);

        if (!inHeap[neighbour->x][neighbour->y]) {
          // If it is not in the heap, add it to the heap.
          node = new Node(neighbour, top, pathLength, distToDest);
          allocated.push_back(node);
          heap.push(node, node->priority());
          inHeap[neighbour->x][neighbour->y] = true;

        } else {
          // If it is in the heap, update the node in the heap.
          Node temp(neighbour);
          int priority = heap.getPriority(&temp);
          if (priority > pathLength + distToDest) {
            heap.updatePriority(&temp, pathLength + distToDest, node);
            node->pathLength = pathLength;
            node->prev = top;
          }
        }
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

  // Deallocate the nodes.
  for (auto ptr : allocated) {
    delete ptr;
  }
  return found;
}

///
/// Returns true if the two nodes contains the same cell.
/// @param the first node 
/// @param the second node
/// @return true if the two nodes contains the same cell, or false otherwise.
///
bool AstarMazeSolver::nodeEquals(Node *a, Node *b) {
  return &a->cell == &b->cell;
}

///
/// Computes the manhattan distance between the two cells.
/// @param the first cell
/// @param the second cell
/// @return the manhattan distance between the two cells.
///
int AstarMazeSolver::distance(Cell &c1, Cell &c2) const {
  return abs(c1.x - c2.x) + abs(c1.y - c2.y);
}
