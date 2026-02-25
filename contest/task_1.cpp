#include <iostream>
#include <cmath>

int main(){
    double v1, a1, v2, a2, S;
    std::cin >> v1 >> a1 >> v2 >> a2 >> S;

    double A = (a1 + a2) / 2.0;
    double B = v1 + v2;
    double C = -S;

    double t;
    if (A == 0){
        t = S / B;
    } else{
        double D = B * B - 4 * A * C;
        double t1 = (-B + std::sqrt(D)) / (2 * A);
        double t2 = (-B - std::sqrt(D)) / (2 * A);
        t = -1;
        if (t1 >= 0) t = t1;
        if (t2 >= 0 && (t < 0 || t2 < t)) t = t2;
    }

    std::cout << (int)t << std::endl;
    return 0;
}
