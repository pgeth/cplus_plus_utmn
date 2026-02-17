// Чтобы задать координаты каждой точки, используйте объявление вещественных переменных, например float xa, ya;
// снабдите программу сообщениями для пользователя: должно быть приглашение на ввод данных и сообщение о выводе результата;
// используйте математическую библиотеку cmath и функцию вычисления корня sqrt.

#include <iostream>
#include <cmath>

float xa, ya;
float xb, yb;
float xc, yc;

int main() {
    std::cout << "Введите координаты точки A: ";
    std::cin >> xa >> ya;

    std::cout << "Введите координаты точки B: ";
    std::cin >> xb >> yb;

    std::cout << "Введите координаты точки C: ";
    std::cin >> xc >> yc;

    float ab = sqrt(pow(xb - xa, 2) + pow(yb - ya, 2));
    float bc = sqrt(pow(xc - xb, 2) + pow(yc - yb, 2));
    float ca = sqrt(pow(xa - xc, 2) + pow(ya - yc, 2));

    float perimeter = ab + bc + ca;

    float s = perimeter / 2;
    float area = sqrt(s * (s - ab) * (s - bc) * (s - ca));

    std::cout << "Длины сторон: AB = " << ab << ", BC = " << bc << ", CA = " << ca << std::endl;
    std::cout << "Периметр: " << perimeter << std::endl;
    std::cout << "Площадь: " << area << std::endl;

    return 0;
}
