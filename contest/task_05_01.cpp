#include <algorithm>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N = 0;
    ifstream fin("input.txt");
    if (fin) {
        fin >> N;
    } else {
        cin >> N;
    }

    int sq = static_cast<int>(sqrt(static_cast<double>(N))) + 1;
    while (static_cast<long long>(sq) * sq > N) --sq;
    while (static_cast<long long>(sq + 1) * (sq + 1) <= N) ++sq;

    vector<char> is_comp(sq + 2, 0);
    vector<int> primes;
    for (int i = 2; i <= sq; ++i) {
        if (!is_comp[i]) {
            primes.push_back(i);
            for (long long j = static_cast<long long>(i) * i; j <= sq; j += i) {
                is_comp[static_cast<int>(j)] = 1;
            }
        }
    }

    const int B = 1 << 16;
    vector<uint32_t> rem(B);
    vector<int> tau(B);

    int bestTau = 0;
    int bestM = 1;

    for (long long lo = 1; lo <= N; lo += B) {
        long long hi = min(static_cast<long long>(N), lo + B - 1);
        int len = static_cast<int>(hi - lo + 1);
        for (int i = 0; i < len; ++i) {
            rem[i] = static_cast<uint32_t>(lo + i);
            tau[i] = 1;
        }

        for (int p : primes) {
            long long start = ((lo + p - 1) / p) * p;
            if (start < static_cast<long long>(p)) start = p;
            for (long long j = start; j <= hi; j += p) {
                int idx = static_cast<int>(j - lo);
                int e = 0;
                uint32_t v = rem[idx];
                while (v % p == 0) {
                    v /= p;
                    ++e;
                }
                rem[idx] = v;
                tau[idx] *= (e + 1);
            }
        }

        for (int i = 0; i < len; ++i) {
            int t = tau[i];
            if (rem[i] > 1) t *= 2;
            int n = static_cast<int>(lo + i);
            if (t > bestTau || (t == bestTau && n > bestM)) {
                bestTau = t;
                bestM = n;
            }
        }
    }

    ofstream fout("output.txt");
    if (fout) {
        fout << bestM << "\n" << bestTau << "\n";
    } else {
        cout << bestM << "\n" << bestTau << "\n";
    }
    return 0;
}
