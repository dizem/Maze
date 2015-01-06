#include "maze.h"

#include <fstream>
#include <cstdio>

void Maze::resize() {
  cells.resize(width);
  for (size_t x = 0; x < cells.size(); x++) {
    cells[x].resize(height);
    for (size_t y = 0; y < cells[x].size(); y++) {
      auto &cell = cells[x][y];
      cell.x = x;
      cell.y = y;
    }
  }
}


void Maze::setSize(int width, int height) {
  if (width <= 0 || height <= 0)
    return;

  this->width = width;
  this->height = height;

  edges.clear();

  resize();
}

void Maze::addEdge(int e1x, int e1y, int e2x, int e2y) {
  edges.push_back({e1x, e1y, e2x, e2y});
  cells[e1x][e1y].adjacents.push_back(&cells[e2x][e2y]);
  cells[e2x][e2y].adjacents.push_back(&cells[e1x][e1y]);
}

bool Maze::load(const std::string &filename) {
  std::ifstream fstr(filename, std::ios::binary);
  if (!fstr.is_open())
    return false;

  // Read width/height/no. of edges.
  int w, h, n;
  fstr.read((char *) &w, sizeof(w));
  fstr.read((char *) &h, sizeof(h));
  fstr.read((char *) &n, sizeof(n));

  if (w <= 0 || h <= 0 || n <= 0)
    return false;

  setSize(w, h);
  edges.resize(n);
  if (!fstr.read((char *) &edges[0], sizeof(Edge) * n))
    return false;
  fstr.close();

  for (auto &edge : edges) {
    if (edge.index1x >= (int) cells.size() 
        || edge.index2x >= (int) cells.size() ||
        edge.index1y >= (int) cells[edge.index1x].size() 
            || edge.index2y >= (int) cells[edge.index2x].size())
      return false;

    auto &cell1 = cells[edge.index1x][edge.index1y];
    auto &cell2 = cells[edge.index2x][edge.index2y];
    cell1.adjacents.push_back(&cell2);
    cell2.adjacents.push_back(&cell1);
  }

  return true;
}

bool Maze::save(const std::string &filename) {
  if (edges.empty() || cells.empty())
    return false;

  std::ofstream fstr(filename, std::ios::binary);
  if (!fstr.is_open())
    return false;

  // Write width/height.
  fstr.write((char *) &width, sizeof(width));
  fstr.write((char *) &height, sizeof(height));

  // Write no. of edges.
  int size = (int) edges.size();
  fstr.write((char *) &size, sizeof(size));

  // Write edges.
  fstr.write((char *) &edges[0], sizeof(Edge) * edges.size());

  return true;
}

bool Maze::saveSVG(const std::string &filename) {
  if (edges.empty())
    return false;

  std::ofstream fstr(filename);
  if (!fstr.is_open())
    return false;

  fstr << "<svg viewBox='0 0 1 1' width='500' height='500'"
      << " xmlns='http://www.w3.org/2000/svg'>\n";
  fstr << "<rect width='1' height='1' style='fill: black' />\n";

  for (int i = 0; i < (int) edges.size(); i++) {
    if (edges[i].index1x >= (int) cells.size()
        || edges[i].index2x >= (int) cells.size() ||
        edges[i].index1y >= (int) cells[edges[i].index1x].size()
            || edges[i].index2y >= (int) cells[edges[i].index2x].size()) {
      fstr.close();
      remove(filename.c_str());
      return false;
    }

    auto &cell1 = cells[edges[i].index1x][edges[i].index1y];
    auto &cell2 = cells[edges[i].index2x][edges[i].index2y];

    if (path.find(edges[i]) == path.end())
      fstr << "<line stroke='white' stroke-width='0.005' ";
    else
      fstr << "<line stroke='red' stroke-width='0.005' ";
    fstr << "x1='" << (float) cell1.x / (float) width << "' y1='" 
        << cell1.y / (float) height << "' ";
    fstr << "x2='" << (float) cell2.x / (float) width << "' y2='" 
        << cell2.y / (float) height << "'/>\n";
  }

  fstr << "</svg>\n";

  return true;
}

void Maze::clear() {
  width = 0;
  height = 0;
  edges.clear();
  cells.clear();
}

void Maze::setPath(std::vector<Cell> path) {
  this->path.clear();
  for (unsigned i = 0; i < path.size() - 1; i++) {
    Cell &a = path[i];
    Cell &b = path[i + 1];
    Edge e1{a.x, a.y, b.x, b.y};
    Edge e2{b.x, b.y, a.x, a.y};
    this->path.insert(e1);
    this->path.insert(e2);
  }
}
