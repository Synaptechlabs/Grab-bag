#include <fstream>
#include <iostream>
#include <string>

auto main(int argc, char *argv[]) -> int {

  std::ifstream file(argv[1]);
  // std::ifstream file("input.txt");
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <filename>\n";
    return 1;
  }
  if (!file) {
    std::cerr << "Could not open file.\n";
    return 1;
  }
  std::string line;
  auto line_number = 0;
  while (std::getline(file, line)) {
    std::cout << "Line: " << line_number << ".\t " << line << '\n';
    ++line_number;
  }

  file.close();
  // std::stringstream buffer;
  // buffer <<file.rdbuf();
  // std::string content = buffer.str();

  // std::cout<<content;
  return 0;
}
