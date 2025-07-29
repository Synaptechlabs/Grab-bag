#include <stdio.h>

int main() {

  int arr[] = {3, 5, 7, 2, 5, 7, 2, 8, 4, 1};
  int n = sizeof(arr) / sizeof(arr[0]);
  for (int i = 0; i < n; ++i) {
    printf("%d\n", arr[i]);
  }
  // start by finding the min value in arr
  for (int i = 0; i < n - 1; ++i) {
    int minIndex = i;
    for (int j = i + 1; j < n; ++j) {
      if (arr[j] < arr[minIndex]) {
        minIndex = j;
      }
    }
    // do the swap
    if (minIndex != i) {
      int temp = arr[i];
      arr[i] = arr[minIndex];
      arr[minIndex] = temp;
    }
  }

  printf("\nAnd here it is sorted:");

  for (int i = 0; i < n; ++i) {
    printf("%d\n", arr[i]);
  }
  return 0;
}
