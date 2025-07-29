#include <iostream>
#include <vector>

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void bubbleSort(std::vector<int> &arr) {
  int n = arr.size();
  for (int i = 0; i < n - 1; ++i)
    for (int j = 0; j < n - i - 1; ++j)
      if (arr[j] > arr[j + 1])
        swap(&arr[j], &arr[j + 1]);
}

auto main() -> int {
  std::vector<int> arr = {5, 2, 6, 7, 2, 5, 8, 9, 1, 0};

  bubbleSort(arr);
  for (int num : arr)
    std::cout << num << " ";
  std::cout << std::endl;

  return 0;
}
