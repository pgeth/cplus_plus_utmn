#include <iostream>
#include <vector>
#include <iomanip>

bool isLeap(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int daysInMonth(int m, int y) {
    static const int d[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (m == 2 && isLeap(y)) return 29;
    return d[m - 1];
}

int main() {
    int d, m, y;
    std::cin >> d >> m >> y;
    int n;
    std::cin >> n;
    std::vector<double> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];

    int maxIdx = 0;
    for (int i = 1; i < n; ++i) {
        if (a[i] > a[maxIdx]) maxIdx = i;
    }

    int growth = 0;
    for (int i = maxIdx; i > 0; --i) {
        if (a[i] > a[i - 1]) ++growth;
        else break;
    }

    for (int i = 0; i < maxIdx; ++i) {
        ++d;
        if (d > daysInMonth(m, y)) {
            d = 1;
            ++m;
            if (m > 12) { m = 1; ++y; }
        }
    }

    std::cout << std::setfill('0') << std::setw(2) << d << '.'
              << std::setw(2) << m << '.'
              << std::setw(4) << y << ' ' << growth << std::endl;
    return 0;
}
