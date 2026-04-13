#include <iostream>
#include <string>
#include <vector>

int main()
{
  int n, m;
  std::cin >> n >> m;
  std::string mask;
  std::cin >> mask;

  int count = 0;
  for (int i = 0; i < n; ++i)
  {
    bool ok = true;
    for (int j = 0; j < m; ++j)
    {
      int x;
      std::cin >> x;
      if (!ok)
        continue;
      char c = mask[j];
      if (c == '+' && x <= 0)
        ok = false;
      else if (c == '-' && x >= 0)
        ok = false;
      else if (c == '.' && x != 0)
        ok = false;
    }
    if (ok)
      ++count;
  }

  if (count == 0)
    std::cout << "No lines with mask";
  else
    std::cout << count;
  return 0;
}
