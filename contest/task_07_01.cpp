#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

int main()
{
  std::ifstream in("input.txt");
  std::ofstream out("output.txt");

  std::string line;
  std::getline(in, line);

  std::vector<std::string> result;
  while (std::getline(in, line))
  {
    if (line.empty())
      continue;

    std::vector<std::string> fields;
    std::stringstream ss(line);
    std::string item;
    while (std::getline(ss, item, ';'))
      fields.push_back(item);

    if (fields.size() < 4)
      continue;

    long long population = std::stoll(fields[2]);
    long long area = std::stoll(fields[3]);

    if (area > 3000000 || population >= 25000000)
      result.push_back(fields[0]);
  }

  std::sort(result.begin(), result.end());
  for (const auto& name : result)
    out << name << '\n';

  return 0;
}
