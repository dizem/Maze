#pragma once

#include <utility>
#include <vector>
#include <stdexcept>
#include <functional>


///
/// Array-based binary heap for A* algorithm.
///
template<typename T>
class BinaryHeap {
private:
  ///
  /// Heap node containing the value and its priority.
  ///
  class HeapNode {
  public:
    T value;
    int priority;

    ///
    /// Constructor
    /// @param value value stored in the node
    /// @param priority priority of the node.
    HeapNode(T value, int priority) : value(value), priority(priority) {
    }
  };

  ///
  /// heap array.
  ///
  std::vector<HeapNode> heap; 
  
  ///
  /// The function to compare values when updating priorities.
  ///
  std::function<bool(const T a, const T b)> equals; 

public:
  ///
  /// Constructor to set the compare function.
  /// @param equals The function to compare values when updating priorities.
  ///
  BinaryHeap(std::function<bool(const T a, const T b)> equals) 
      : equals(equals) {
  }

  ///
  /// Pushes a value and its priority to the heap.
  /// @param value the value to add.
  /// @param priority the priority of the value.
  ///
  void push(const T &value, int priority);

  ///
  /// Pops the top value from the heap.
  /// @return the value stored in the top node.
  ///
  T pop();

  ///
  /// @return true if the heap is empty, or false otherwise.
  ///
  bool empty() const;

  ///
  /// @return the priority of the given value, or -1 if the value doesn't exist.
  ///
  int getPriority(const T &value) const;

  ///
  /// Updates the priority of the given value.
  /// @param value the value to be updated.
  /// @param priority the new priority to set.
  /// @param ref reference of the value in the heap.
  /// @return true if updated successfully, false if the value doesn't exist.
  ///
  bool updatePriority(const T &value, int priority, T &ref);
};

///
/// Pushes a value and its priority to the heap.
/// @param value the value to add.
/// @param priority the priority of the value.
///
template<typename T>
void BinaryHeap<T>::push(const T &value, int priority) {
  // Add a new value to the end of heap array.
  heap.push_back(HeapNode(value, priority));
  // Heapify.
  for (unsigned i = heap.size() - 1;
       i > 0 && heap[i].priority < heap[(i - 1) / 2].priority; i = (i - 1) / 2) {
    std::swap(heap[i], heap[(i - 1) / 2]);
  }
}

///
/// Pops the top value from the heap.
/// @return the value stored in the top node.
///
template<typename T>
T BinaryHeap<T>::pop() {
  // If the heap is empty, throw an underflow error.
  if (empty()) {
    throw std::underflow_error("");
  }

  T top = heap[0].value;
  // Move the last node to the top.
  heap[0] = heap.back();
  heap.pop_back();

  // Heapify.
  unsigned i = 0;
  while (i < heap.size() - 1) {
    unsigned smallest = i;
    if (i * 2 + 1 < heap.size() && heap[i * 2 + 1].priority < heap[smallest].priority)
      smallest = i * 2 + 1;
    if (i * 2 + 2 < heap.size() && heap[i * 2 + 2].priority < heap[smallest].priority)
      smallest = i * 2 + 2;
    if (i != smallest) {
      std::swap(heap[i], heap[smallest]);
      i = smallest;
    } else {
      break;
    }
  }
  return top;
}

///
/// @return true if the heap is empty, or false otherwise.
///
template<typename T>
bool BinaryHeap<T>::empty() const {
  return heap.empty();
}

///
/// @return the priority of the given value, or -1 if the value doesn't exist.
///
template<typename T>
int BinaryHeap<T>::getPriority(const T &value) const {
  for (unsigned i = 0; i < heap.size(); i++) {
    if (equals(heap[i].value, value)) {
      return heap[i].priority;
    }
  }
  return -1;
}

///
/// Updates the priority of the given value.
/// @param value the value to be updated.
/// @param priority the new priority to set.
/// @param ref reference of the value in the heap.
/// @return true if updated successfully, false if the value doesn't exist.
///
template<typename T>
bool BinaryHeap<T>::updatePriority(const T &value, int priority, T &ref) {
  for (unsigned i = 0; i < heap.size(); i++) {
    // If value is found, 
    if (equals(heap[i].value, value)) {
      ref = heap[i].value;
      // If the new priority is greater than the old one, 
      if (priority > heap[i].priority) {
        heap[i].priority = priority;
        // sift down 
        while (i < heap.size() - 1) {
          unsigned smallest = i;
          if (i * 2 + 1 < heap.size() 
              && heap[i * 2 + 1].priority < heap[smallest].priority)
            smallest = i * 2 + 1;
          if (i * 2 + 2 < heap.size() 
              && heap[i * 2 + 2].priority < heap[smallest].priority)
            smallest = i * 2 + 2;
          if (smallest != i) {
            std::swap(heap[i], heap[smallest]);
            i = smallest;
          } else {
            break;
          }
        }

      } else if (priority < heap[i].priority) {
        // If the new priority is less than the old one
        heap[i].priority = priority;
        // sift up 
        for (unsigned j = i; j > 0 
            && heap[j].priority < heap[(j - 1) / 2].priority;
             j = (j - 1) / 2) {
          std::swap(heap[j], heap[(j - 1) / 2]);
        }
      }
      break;
    }
  }
  return false;
}
