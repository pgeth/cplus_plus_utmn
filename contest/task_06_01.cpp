#include <fstream>
#include <vector>

int main()
{
  std::ifstream in("input.txt");
  std::ofstream out("output.txt");

  int n, m;
  in >> n >> m;

  std::vector<std::vector<double>> mat(n, std::vector<double>(m, 0.0));

  int i;
  while (in >> i && i != -1)
  {
    int ni;
    in >> ni;
    for (int k = 0; k < ni; ++k)
    {
      double a;
      int j;
      in >> a >> j;
      mat[i][j] = a;
    }
  }

  bool first = true;
  for (int r = 0; r < n; ++r)
  {
    bool zero = true;
    for (int c = 0; c < m; ++c)
    {
      if (mat[r][c] != 0.0)
      {
        zero = false;
        break;
      }
    }
    if (zero)
    {
      if (!first)
        out << ' ';
      out << r;
      first = false;
    }
  }
  out << '\n';

  int bestCol = 0;
  double bestSum = 0.0;
  for (int c = 0; c < m; ++c)
  {
    double s = 0.0;
    for (int r = 0; r < n; ++r)
      s += mat[r][c];
    if (c == 0 || s > bestSum)
    {
      bestSum = s;
      bestCol = c;
    }
  }
  out << bestCol << '\n';

  return 0;
}
