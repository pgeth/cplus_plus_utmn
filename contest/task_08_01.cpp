#include <cmath>
#include <fstream>
#include <string>
#include <vector>

int main()
{
  std::ifstream in("input.txt");
  std::ofstream out("output.txt");

  std::vector<double> areas;
  std::string shape;
  while (in >> shape)
  {
    double x, y;
    in >> x >> y;
    double area = 0.0;

    if (shape == "Rectangle")
    {
      double a, b;
      in >> a >> b;
      area = a * b;
    }
    else if (shape == "Square")
    {
      double a;
      in >> a;
      area = a * a;
    }
    else if (shape == "Diamond")
    {
      double a, alpha;
      in >> a >> alpha;
      area = a * a * std::sin(alpha * M_PI / 180.0);
    }
    else if (shape == "Circle")
    {
      double r;
      in >> r;
      area = M_PI * r * r;
    }

    areas.push_back(area);
  }

  double maxArea = 0.0;
  for (double a : areas)
    if (a > maxArea)
      maxArea = a;

  const double eps = 1e-9;
  for (size_t i = 0; i < areas.size(); ++i)
    if (std::fabs(areas[i] - maxArea) < eps)
      out << (i + 1) << '\n';

  return 0;
}
