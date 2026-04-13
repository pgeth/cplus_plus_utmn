#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    int N;
    std::cin >> N;

    std::vector<int> ratings(N);
    for (int i = 0; i < N; ++i)
        std::cin >> ratings[i];

    std::vector<int> excellentIdx;
    std::vector<int> failingIdx;
    for (int i = 0; i < N; ++i)
    {
        if (ratings[i] >= 90)
            excellentIdx.push_back(i);
        else if (ratings[i] < 60)
            failingIdx.push_back(i);
    }

    if (excellentIdx.empty() || failingIdx.empty())
    {
        std::cout << "Impossible";
        return 0;
    }

    std::stable_sort(excellentIdx.begin(), excellentIdx.end(),
                     [&](int a, int b) { return ratings[a] > ratings[b]; });

    int mentors = std::min<int>(3, excellentIdx.size());
    int failing = failingIdx.size();
    int groups = std::min(mentors, failing);

    int base = failing / groups;
    int extra = failing % groups;

    int pos = 0;
    for (int g = 0; g < groups; ++g)
    {
        int size = base + (g < extra ? 1 : 0);
        std::cout << ratings[excellentIdx[g]];
        for (int k = 0; k < size; ++k)
            std::cout << ' ' << ratings[failingIdx[pos++]];
        if (g + 1 < groups)
            std::cout << '\n';
    }
}
