#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class Student
{
public:
  std::string name;
  int marks[5];
  double criterion() const
  {
    return (marks[0] + marks[1] + marks[2] + marks[3] + marks[4]) / 5.0;
  }
};

class Employee
{
public:
  std::string name;
  std::string position;
  long long salary;
  long long criterion() const { return salary; }
};

class Player
{
public:
  std::string name;
  std::string team;
  long long points;
  long long criterion() const { return points; }
};

template <typename T>
const T* findBest(const std::vector<T>& v)
{
  if (v.empty())
    return nullptr;
  const T* best = &v[0];
  for (size_t i = 1; i < v.size(); ++i)
  {
    if (v[i].criterion() > best->criterion())
      best = &v[i];
  }
  return best;
}

int main()
{
  std::vector<Student> students;
  std::vector<Employee> employees;
  std::vector<Player> players;

  std::string line;
  while (std::getline(std::cin, line))
  {
    if (line.empty())
      continue;
    std::istringstream iss(line);
    std::string name;
    iss >> name;
    if (name.rfind("Student", 0) == 0)
    {
      Student s;
      s.name = name;
      for (int i = 0; i < 5; ++i)
        iss >> s.marks[i];
      students.push_back(s);
    }
    else if (name.rfind("Employee", 0) == 0)
    {
      Employee e;
      e.name = name;
      iss >> e.position >> e.salary;
      employees.push_back(e);
    }
    else if (name.rfind("Player", 0) == 0)
    {
      Player p;
      p.name = name;
      iss >> p.team >> p.points;
      players.push_back(p);
    }
  }

  if (auto* bs = findBest(students))
    std::cout << bs->name << "\n";
  if (auto* be = findBest(employees))
    std::cout << be->name << "\n";
  if (auto* bp = findBest(players))
    std::cout << bp->name << "\n";
}
