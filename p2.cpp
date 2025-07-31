#include<iostream>
#include<vector>

void ithTerm(const std::vector<int>& a){
  for (int i = 0; i < a.size(); ++i) {
    
    //LHS
    for (int j = i - 1; j >= 0; --j) {
      std::cout << a[i-j-1] <<",";
    }
    
    //ith term
    std::cout << "[" << a[i] << "]";
    
    //RHS
    for (int k = i + 1; k < a.size(); ++k) {
      std::cout << ","<<a[k];
    }
    
    std::cout << "\n";
  }
}

auto main() -> int {
  std::string s = "Hello";
  std::vector<char> v(s.begin(), s.end());
  std::vector<int> a = {3, 5, 1, 9, 8, 4, 2, 43, 13, 15, 12, 19, 7};
  ithTerm(a);
  std::cout << "\n";
}