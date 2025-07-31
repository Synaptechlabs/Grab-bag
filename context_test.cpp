#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::string displayContextLine(const std::vector<int> &a, int i) {
  std::ostringstream oss;

  for (int j = i - 1; j >= 0; --j) {
    oss << a[i - j - 1] << ",";
  }

  oss << "[" << a[i] << "]";

  for (int k = i + 1; k < a.size(); ++k) {
    oss << "," << a[k];
  }

  return oss.str();
}

void runTests() {
  std::vector<int> data = {3, 5, 1, 9, 8};

  assert(displayContextLine(data, 0) == "[3],5,1,9,8");
  assert(displayContextLine(data, 1) == "3,[5],1,9,8");
  assert(displayContextLine(data, 2) == "3,5,[1],9,8");
  assert(displayContextLine(data, 3) == "3,5,1,[9],8");
  assert(displayContextLine(data, 4) == "3,5,1,9,[8]");

  std::cout << "✅ All tests passed.\n";
}

int main() {
  runTests();
  return 0;
}
