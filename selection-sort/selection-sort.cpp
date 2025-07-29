#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>

std::vector<int> generateRandomArray(size_t size, int minVal, int maxVal) {
  std::vector<int> result;
  result.reserve(size);

  std::random_device rd;  // Non-deterministic random seed
  std::mt19937 gen(rd()); // Mersenne Twister RNG
  std::uniform_int_distribution<> dist(minVal, maxVal);

  for (size_t i = 0; i < size; ++i) {
    result.push_back(dist(gen));
  }

  return result;
}

void selectionSort(std::vector<int> &arr) {
  int minIndex = 0;
  auto n = std::size(arr);
  for (auto i = 0; i < n; ++i) {
    minIndex = i;
    for (auto j = i + 1; j < n; ++j) {
      if (arr[j] < arr[minIndex])
        minIndex = j;
    }
    std::swap(arr[i], arr[minIndex]);
  }
}

auto main() -> int {
  std::cout << "\nHello\n";
  // create a test vector
  // std::vector<int> testArray = {1, 5, 6, 3, 4, 7, 9, 2};
  auto testArray = generateRandomArray(10000, 1, 10000);
  for (int num : testArray) {
    std::cout << num << "\n";
  }

  auto start = std::chrono::high_resolution_clock::now();

  selectionSort(testArray);

  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration = end - start;

  /*int minIndex = 0;
  // auto n=static_cast<int>(testArray.size());
  auto n = std::size(testArray);
  // now do the selection sort
  for (auto i = 0; i < n; ++i) {
    minIndex = i;
    for (auto j = i + 1; j < n; ++j) {
      if (testArray[j] < testArray[minIndex])
        minIndex = j;
    }
    std::swap(testArray[i], testArray[minIndex]);
  }
  */
  // print output
  std::cout << "\nSorted\n\n";
  for (int num : testArray) {
    std::cout << num << "\n";
  }

  std::cout << "\nSelection Sort took " << duration.count() << " ms\n";
  return 0;
}
