#include "disjointSets.h"

///
/// Constructs a disjoint set with the given size.
/// @param n size of the disjoint set.
///
DisjointSets::DisjointSets(int n) {
  s.resize((unsigned) n, -1);
}

///
/// Unions the sets of the two given numbers.
/// @param a the first number
/// @param a the second number
///
void DisjointSets::setUnion(int a, int b) {
  // If a and b are invalid, return.
  if (a < 0 || a >= (int) s.size() || b < 0 || b >= (int) s.size()) {
    return;
  }
  // Find the set labels of a and b
  int root1 = findSet(a);
  int root2 = findSet(b);

  // Union the two sets.
  int newSize = s[root1] + s[root2];
  if (s[root1] <= s[root2]) {
    s[root2] = root1;
    s[root1] = newSize;

  } else {
    s[root1] = root2;
    s[root2] = newSize;
  }
}

///
/// Returns the set label of the given number.
/// @param i the given number
/// @return set label of the given number.
///
int DisjointSets::findSet(int i) {
  if (s[i] < 0) {
    return i;
  } else {
    return findSet(s[i]);
  }
}