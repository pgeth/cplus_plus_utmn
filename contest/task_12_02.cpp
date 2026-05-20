#include <iostream>
#include <stack>
#include <string>
#include <utility>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s;
    std::getline(std::cin, s);

    auto isOpen = [](char c) {
        return c == '(' || c == '[' || c == '{';
    };
    auto isClose = [](char c) {
        return c == ')' || c == ']' || c == '}';
    };
    auto matches = [](char o, char c) {
        return (o == '(' && c == ')') ||
               (o == '[' && c == ']') ||
               (o == '{' && c == '}');
    };

    std::stack<std::pair<char, int>> st;
    for (int i = 0; i < (int)s.size(); ++i) {
        char c = s[i];
        if (isOpen(c)) {
            st.push({c, i});
        } else if (isClose(c)) {
            if (st.empty() || !matches(st.top().first, c)) {
                std::cout << (i + 1) << "\n";
                return 0;
            }
            st.pop();
        }
    }

    if (!st.empty()) {
        int firstUnmatched = -1;
        while (!st.empty()) {
            firstUnmatched = st.top().second;
            st.pop();
        }
        std::cout << (firstUnmatched + 1) << "\n";
    } else {
        std::cout << "OK" << "\n";
    }

    return 0;
}
