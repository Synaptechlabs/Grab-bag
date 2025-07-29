#include <iostream>
#include <string>

void permute(const std::string& s, const std::string& output) {
    if (s.empty()) {
        std::cout << output << std::endl;
        return;
    }

    for (size_t i = 0; i < s.length(); ++i) {
        std::string remaining = s.substr(0, i) + s.substr(i + 1);
        permute(remaining, output + s[i]);
    }
}

int main() {
    std::string s = "Abcdefghijk";
    permute(s, "");
    return 0;
}

