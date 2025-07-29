#include <iostream>
#include <vector>

auto main() -> int {
  // std::cout << "hello";

  std::vector<int> arr = {4, 5, 6, 7, 2, 1, 7, 8, 5};
  // std::cout << arr[1];
  int minIndex = 0;
  auto n = std::size(arr);

  // now try again
  for (auto i = 0; i < n; ++i) {
    // std::cout << minIndex << "\n";
    minIndex = i;
    for (auto j = 0; j < i + 1; ++j) {
      if (arr[j] < arr[minIndex])
        minIndex = j;
    }
    std::swap(arr[i], arr[minIndex]);
  }

  for (auto i = 0; i < n; ++i)
    std::cout << arr[i] << "\n";

  return 0;
}
