/*
 * pivot_visualize.cpp
 *
 * Description:
 *   This utility visually highlights the pivot element at each iteration
 *   of a linear scan through a vector. For each position `i`, the output
 *   prints:
 *     - All elements before `i` in **left-to-right** order,
 *     - The current pivot element `a[i]` in brackets,
 *     - All elements after `i` in normal order.
 *
 *   Internally, this is done by iterating backward over the left partition,
 *   but mapping indices cleverly so the output reads forward. 
 *   A compact, elegant trick — surprisingly rare in typical textbooks.
 *
 * Example Output:
 *   For input: {3, 5, 1, 9}
 *   Output:
 *     [3],5,1,9
 *     3,[5],1,9
 *     3,5,[1],9
 *     3,5,1,[9]
 *
 * Author: Scott Douglass (2025)
 * Inspired by: hands-on exploration of loop mechanics and permutation logic
 * License: MIT
 */

#include <cstring>
#include <iostream>
#include <vector>

// Same thing, different day :)
template<typename T>
void printPartitionedView(const std::vector<T>& data) {
    for (size_t i = 0; i < data.size(); ++i) {
        for (size_t j = i - 1; j != static_cast<size_t>(-1); --j) {
            std::cout << data[i - j - 1] << ",";
        }

        std::cout << "[" << data[i] << "]";

        for (size_t k = i + 1; k < data.size(); ++k) {
            std::cout << "," << data[k];
        }
        std::cout << "\n";
    }
}

void pivot_visualize(const std::vector<int>& a, const std::string& label = "Pivot View") {
    std::cout << "--- " << label << " ---\n";
    for (int i = 0; i < a.size(); ++i) {
        for (int j = i - 1; j >= 0; --j) {
            std::cout << a[i - j - 1] << ",";
        }

        std::cout << "[" << a[i] << "]";
        for (int k = i + 1; k < a.size(); ++k) {
            std::cout << "," << a[k];
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

// Example usage
int main() {
    std::vector<int> a = {3, 5, 1, 9, 8, 4, 2, 43, 13, 15, 12, 19, 7};
    pivot_visualize(a, "Demo Pivot Tracker");
    return 0;
}

/*
auto main() -> int {
  std::string s = "Hello";
  std::vector<char> v(s.begin(), s.end());
  std::vector<int> a = {3, 5, 1, 9,8,4,2,43,13,15,12,19,7};

  for (int i = 0; i < a.size(); ++i) {
    for (int j = i - 1; j >= 0; --j) {
      std::cout << a[i-j-1] <<",";
    }

    std::cout << "[" << a[i] << "]";
    for (int k = i + 1; k < a.size(); ++k) {
      std::cout << ","<<a[k];
    }
    std::cout << "\n";
  }

  std::cout << "\n";
}
*/