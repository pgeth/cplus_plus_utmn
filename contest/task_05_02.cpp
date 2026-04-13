#include <iostream>
#include <queue>
#include <vector>

int main()
{
  int n;
  std::cin >> n;
  std::vector<std::vector<int>> grid(n, std::vector<int>(n));
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      std::cin >> grid[i][j];

  std::vector<std::vector<bool>> visited(n, std::vector<bool>(n, false));
  int count = 0;
  const int dr[4] = {-1, 1, 0, 0};
  const int dc[4] = {0, 0, -1, 1};

  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < n; ++j)
    {
      if (grid[i][j] != 0 || visited[i][j])
        continue;
      ++count;
      std::queue<std::pair<int, int>> q;
      q.push({i, j});
      visited[i][j] = true;
      while (!q.empty())
      {
        auto [r, c] = q.front();
        q.pop();
        for (int k = 0; k < 4; ++k)
        {
          int nr = r + dr[k];
          int nc = c + dc[k];
          if (nr < 0 || nr >= n || nc < 0 || nc >= n)
            continue;
          if (visited[nr][nc] || grid[nr][nc] != 0)
            continue;
          visited[nr][nc] = true;
          q.push({nr, nc});
        }
      }
    }
  }

  std::cout << count;
  return 0;
}
