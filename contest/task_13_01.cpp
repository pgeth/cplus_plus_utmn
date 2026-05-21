#include <iostream>
#include <string>

int main() {
    std::string s;
    std::getline(std::cin, s);

    int i = 0;
    while (i < (int)s.size()) {
        int j = i;
        while (j < (int)s.size() && s[j] == s[i]) ++j;
        std::cout << (j - i) << " '" << s[i] << "'\n";
        i = j;
    }
}
