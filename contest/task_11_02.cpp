#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>

int main()
{
  std::vector<double> xs, ys, rs;
  double x, y, r;
  while (std::cin >> x >> y >> r)
  {
    xs.push_back(x);
    ys.push_back(y);
    rs.push_back(r);
  }

  if (xs.empty())
  {
    std::cout << 0;
    return 0;
  }

  double minX = xs[0] - rs[0];
  double maxX = xs[0] + rs[0];
  double minY = ys[0] - rs[0];
  double maxY = ys[0] + rs[0];
  for (size_t i = 1; i < xs.size(); ++i)
  {
    minX = std::min(minX, xs[i] - rs[i]);
    maxX = std::max(maxX, xs[i] + rs[i]);
    minY = std::min(minY, ys[i] - rs[i]);
    maxY = std::max(maxY, ys[i] + rs[i]);
  }

  std::mt19937 gen(123456789);
  std::uniform_real_distribution<double> distX(minX, maxX);
  std::uniform_real_distribution<double> distY(minY, maxY);

  std::vector<double> r2(rs.size());
  for (size_t i = 0; i < rs.size(); ++i)
    r2[i] = rs[i] * rs[i];

  const int N = 1000000;
  int inside = 0;
  for (int i = 0; i < N; ++i)
  {
    double px = distX(gen);
    double py = distY(gen);
    for (size_t j = 0; j < xs.size(); ++j)
    {
      double dx = px - xs[j];
      double dy = py - ys[j];
      if (dx * dx + dy * dy <= r2[j])
      {
        ++inside;
        break;
      }
    }
  }

  double area = static_cast<double>(inside) / N * (maxX - minX) * (maxY - minY);
  long long rounded = static_cast<long long>(std::round(area / 10.0)) * 10;
  std::cout << rounded;
}
