#include <iostream>
#include <format>
#include <string>

int hexValue(char c)
{
  if (c >= '0' && c <= '9')
    return c - '0';
  if (c >= 'A' && c <= 'F')
    return c - 'A' + 10;
  if (c >= 'a' && c <= 'f')
    return c - 'a' + 10;
  return -1;
}

int main()
{
  int N;
  std::cin >> N;
  std::string hexStr = std::format("{:x}", N);

  int maxValue = 0;
  char maxChar = '0';

  for (char c : hexStr)
  {
    int v = hexValue(c);
    if (v > maxValue)
    {
      maxValue = v;
      maxChar = std::toupper(static_cast<unsigned char>(c));
    }
  }

  if (maxValue >= 0 && maxValue <= 9)
  {
    N = N * 2;
  }
  else if (maxChar == 'A' || maxChar == 'D')
  {
    if (N < 10)
    {
      N = 0;
    }
    else
    {
      N /= 10;
    }
  }
  else if (maxChar == 'E')
  {
    N = N + 1;
  }
  else if (maxChar == 'F')
  {
    int sum = 0;
    int t = N;
    while (t > 0)
    {
      sum += t % 10;
      t /= 10;
    }
    N = N + sum;
  }
  else if (maxChar == 'B' || maxChar == 'C')
  {
    std::string s = std::to_string(N);
    std::swap(s.front(), s.back());
    N = std::stoll(s);
  }

  std::cout << N;
}
