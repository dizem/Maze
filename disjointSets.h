#pragma once

#include <vector>

///
/// Disjoint sets for the Kruskal's algorithm.
///
class DisjointSets {
private:
  /// Set label of each number.
  std::vector<int> s;

public:
  ///
  /// Constructs a disjoint set with the given size.
  /// @param n size of the disjoint set.
  ///
  DisjointSets(int n);

  ///
  /// Unions the sets of the two given numbers.
  /// @param a the first number
  /// @param a the second number
  ///
  void setUnion(int a, int b);

  ///
  /// Returns the set label of the given number.
  /// @param i the given number
  /// @return set label of the given number.
  ///
  int findSet(int i);
};

