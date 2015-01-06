#pragma once

#include <string>
#include <vector>
#include <set>

///
/// Stores a single cell in the maze grid. Provides the location of the cell, and any cells connected to it.
///
struct Cell
{
	int x;									///< x position of cell in the grid.
	int y;									///< y position of cell in the grid.
	std::vector<Cell*> adjacents;			///< list of cells connected to this cell during maze generation.

	///
	/// Default constructor used to initialise an empty cell, or to create a cell with a given x,y value.
	/// @param x the x location of the cell in the grid, defaults to 0.
	/// @param y the y location of the cell in the grid, defaults to 0.
	///
	Cell(int x = 0, int y = 0) : x(x), y(y) {}
};

///
/// Edge stores the location of two cells (A and B) that are joined together.
/// Index values reference locations in the cell grid.
///
struct Edge
{
	int index1x;							///< x value of the index of cell A.
	int index1y;							///< y value of the index of cell A.
	int index2x;							///< x value of the index of cell B.
	int index2y;							///< y value of the index of cell B.
  
  bool operator<(const Edge& other) const {
    if (index1x != other.index1x)
      return index1x < other.index1x;
    if (index1y != other.index1y)
      return index1y < other.index1y;
    if (index2x != other.index2x)
      return index2x < other.index2x;
    return index2y < other.index2y;
  }
};

///
/// Maze Graph implemented as a 2D grid.
///
class Maze
{
private:
	std::vector<Edge> edges;				      ///< All edges in the maze. Used to simplify maze loading/saving.
	std::vector<std::vector<Cell>> cells;	///< 2D grid of all cells in the maze.
  std::set<Edge> path;                  ///< Set of edges in the path.
	int width;								            ///< Width of the grid (no. of columns).
	int height;								            ///< Height of the grid (no. of rows).

private:
	///
	/// Allocates memory for the cells grid, based on the stored width/height.
	///
	void resize();

public:
	///
	/// Default constructor that creates an empty maze, of 0 width/height.
	///
	Maze() : width(0), height(0) {}

	///
	/// Sets the width/height of the maze, and clears all maze data, then allocates appropriate memory matching the new size by calling resize().
	///
	void setSize(int width, int height);

	///
	/// Adds a new edge to the maze by adding an Edge to the edge list, and adding to the adjacents of both cells.
	/// @param e1x x value of the index of cell A.
	/// @param e1y y value of the index of cell A.
	/// @param e2x x value of the index of cell B.
	/// @param e2y y value of the index of cell B.
	///
	void addEdge(int e1x, int e1y, int e2x, int e2y);

	///
	/// Returns the 2D grid of all cells in the maze. Used by any class that needs to generate a maze and populate the cells.
	/// @return the 2D grid of cells.
	///
	std::vector<std::vector<Cell>> &getCells() { return cells; }

	///
	/// Loads a maze from a given binary .maze file.
	/// @param filename the path and filename matching the binary .maze file to be loaded relative to the exe.
	/// @return false if file does not exist, or maze file contains bad data, otherwise true.
	///
	bool load(const std::string &filename);

	///
	/// Saves a binary .maze file.
	/// @param filename the path and filename matching the binary .maze file to be saved relative to the exe.
	/// @return false if file cannot be created, or maze contains data that cannot be saved, otherwise true.
	///
	bool save(const std::string &filename);

	///
	/// Saves an SVG representation of the maze.
	/// @param filename the path and filename matching the .svg file to be saved relative to the exe.
	/// @return false if file cannot be created or maze contains no edges, otherwise true.
	///
	bool saveSVG(const std::string &filename);

	///
	/// Accessor for the width of the maze (no. of columns in the 2D grid).
	/// @return value stored in width.
	///
	int getWidth() const { return width; }

	///
	/// Accessor for the height of the maze (no. of rows in the 2D grid).
	/// @return value stored in height.
	///
	int getHeight() const { return height; }

	///
	/// Clears all data stored by the maze, and frees all memory. Resets the size of the maze to 0 width/height.
	///
	void clear();
  
  ///
  /// Sets the path to the maze.
  /// @param path cells in the path.
  ///
  void setPath(std::vector<Cell> path);
};
