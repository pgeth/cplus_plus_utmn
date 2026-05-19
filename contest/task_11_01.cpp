#include <iostream>
#include <cmath>

int main()
{
  double a, b;
  char op;
  int count = 0;

  while (std::cin >> a >> op >> b)
  {
    double result = 0.0;
    switch (op)
    {
      case '+': result = a + b; break;
      case '-': result = a - b; break;
      case '*': result = a * b; break;
      case '/': result = a / b; break;
    }

    if (std::isnan(result) || std::isinf(result))
    {
      ++count;
    }
    else if (result == 0.0)
    {
      bool expectedZero = false;
      switch (op)
      {
        case '+': expectedZero = (a == -b); break;
        case '-': expectedZero = (a == b); break;
        case '*': expectedZero = (a == 0.0 || b == 0.0); break;
        case '/': expectedZero = (a == 0.0); break;
      }
      if (!expectedZero)
        ++count;
    }
  }

  std::cout << count;
}
