#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <string>

int main()
{
  std::ifstream in("input.txt");
  std::ofstream out("output.txt");

  std::map<std::string, int> group_students;
  std::map<std::string, std::set<std::string>> professor_groups;

  std::string line;
  while (std::getline(in, line))
  {
    if (line.empty())
      continue;
    std::stringstream ss(line);
    std::string id, second, third;
    std::getline(ss, id, ';');
    std::getline(ss, second, ';');
    if (std::getline(ss, third, ';'))
    {
      professor_groups[id].insert(third);
    }
    else
    {
      group_students[second] += 1;
    }
  }

  std::string best_id;
  int best_count = -1;
  for (const auto &[prof, groups] : professor_groups)
  {
    int total = 0;
    for (const auto &g : groups)
    {
      auto it = group_students.find(g);
      if (it != group_students.end())
        total += it->second;
    }
    if (total > best_count)
    {
      best_count = total;
      best_id = prof;
    }
  }

  out << best_id;
  return 0;
}
