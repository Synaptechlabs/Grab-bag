#include<iostream>
#include<fstream>
#include<sstream>
#include<string>

auto main()->int{
    std::cout<<"Hello\n";
    std::ifstream file("input.txt");

    if(!file){
        std::cerr<<"Could not open file.\n";
        return 1;
    }

    std::stringstream buffer;
    buffer <<file.rdbuf();
    std::string content = buffer.str();

    std::cout<<content;
    return 0;
}
