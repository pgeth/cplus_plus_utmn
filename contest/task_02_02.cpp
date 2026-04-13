#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int main()
{
  int N;
  cin >> N;

  vector<int> day(N), night(N);
  for (int i = 0; i < N; ++i)
  {
    cin >> day[i] >> night[i];
  }

  int middleDayTemp = 1;
  int middleDayDiff = day[0] - night[0];

  for (int i = 1; i < N; ++i)
  {
    int diff = day[i] - night[i]; // без abs
    if (diff < middleDayDiff)
    {
      middleDayDiff = diff;
      middleDayTemp = i + 1;
    }
  }

  cout << middleDayTemp << '\n';

  int positiveCount = 0;
  for (int i = 0; i < N; ++i)
  {
    if (day[i] > 0)
      positiveCount++;
  }

  if (positiveCount == 0)
  {
    cout << "No positive data\n";
  }
  else if (positiveCount == N)
  {
    cout << "All data are positive\n";
  }
  else
  {
    bool first = true;
    for (int i = 0; i < N; ++i)
    {
      if (day[i] > 0)
      {
        if (!first)
          cout << ' ';
        cout << day[i];
        first = false;
      }
    }
    cout << '\n';
  }

  return 0;
}
