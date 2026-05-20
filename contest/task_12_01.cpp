#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::string> names(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> names[i];
    }

    std::vector<std::vector<int>> dist(n, std::vector<int>(n, 0));
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            int v;
            std::cin >> v;
            dist[i][j] = v;
            dist[j][i] = v;
        }
    }

    std::vector<std::string> result;
    for (int i = 0; i < n; ++i) {
        bool connectedToAll = true;
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            if (dist[i][j] == 0) {
                connectedToAll = false;
                break;
            }
        }
        if (connectedToAll) {
            result.push_back(names[i]);
        }
    }

    if (result.empty()) {
        std::cout << "NO" << "\n";
    } else {
        std::sort(result.begin(), result.end());
        for (const auto& name : result) {
            std::cout << name << "\n";
        }
    }

    return 0;
}
