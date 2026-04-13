#include <algorithm>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

int main()
{
  std::ifstream in("input.txt");
  std::ofstream out("output.txt");

  std::string line;
  std::getline(in, line);

  std::map<std::string, std::pair<int, int>> stats;

  while (std::getline(in, line))
  {
    if (line.empty())
      continue;
    std::vector<std::string> fields;
    std::string field;
    std::stringstream ss(line);
    while (std::getline(ss, field, ';'))
      fields.push_back(field);
    if (fields.size() < 6)
      continue;
    const std::string &region = fields[1];
    double literacy = std::stod(fields.back());
    auto &s = stats[region];
    s.first += 1;
    if (literacy > 90.0)
      s.second += 1;
  }

  double best = -1.0;
  std::vector<std::string> best_regions;
  for (const auto &[region, s] : stats)
  {
    double ratio = static_cast<double>(s.second) / s.first;
    if (ratio > best)
    {
      best = ratio;
      best_regions.clear();
      best_regions.push_back(region);
    }
    else if (ratio == best)
    {
      best_regions.push_back(region);
    }
  }

  std::sort(best_regions.begin(), best_regions.end());
  for (std::size_t i = 0; i < best_regions.size(); ++i)
  {
    if (i > 0)
      out << '\n';
    out << best_regions[i];
  }
  return 0;
}
