#include <iostream>
#include <vector>

int main()
{
  int n;
  std::cin >> n;
  std::vector<int> parent(n);
  for (int i = 0; i < n; ++i)
    std::cin >> parent[i];

  std::vector<int> depth(n, 0);
  std::vector<int> path;
  path.reserve(n);
  int maxDepth = 0;

  for (int i = 0; i < n; ++i)
  {
    if (depth[i] != 0)
      continue;
    path.clear();
    int cur = i;
    while (cur != -1 && depth[cur] == 0)
    {
      path.push_back(cur);
      cur = parent[cur];
    }
    int base = (cur == -1) ? 0 : depth[cur];
    for (int j = static_cast<int>(path.size()) - 1; j >= 0; --j)
    {
      ++base;
      depth[path[j]] = base;
      if (base > maxDepth)
        maxDepth = base;
    }
  }

  std::cout << maxDepth;
}
