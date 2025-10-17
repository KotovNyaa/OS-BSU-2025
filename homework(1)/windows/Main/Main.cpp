#include "../numberLIB/number.h"
#include "../vectorLIB/vector.h"
#include <iostream>
#include <Windows.h>

void printVector(const std::string& name, const Vector& v) {
    std::cout << name << " = (" << v.getValue_x().getValue() << ", "
        << v.getValue_y().getValue() << ")" << std::endl;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::cout << "--- Демонстрация библиотеки Number ---" << std::endl;

    Number a(15.5);
    Number b(3.0);
    Number zero = Number::Zero();
    Number one = Number::One();

    std::cout << "a = " << a.getValue() << std::endl;
    std::cout << "b = " << b.getValue() << std::endl;
    std::cout << "Number::Zero() = " << zero.getValue() << std::endl;
    std::cout << "Number::One() = " << one.getValue() << std::endl;

    Number sum = a + b;
    Number diff = a - b;
    Number prod = a * b;
    Number quot = a / b;

    std::cout << "a + b = " << sum.getValue() << std::endl;
    std::cout << "a - b = " << diff.getValue() << std::endl;
    std::cout << "a * b = " << prod.getValue() << std::endl;
    std::cout << "a / b = " << quot.getValue() << std::endl;

    std::cout << "\n--- Демонстрация библиотеки Vector ---" << std::endl;

    Vector v1(Number(3.0), Number(4.0));
    Vector v2(Number(1.0), Number(2.0));

    printVector("Вектор v1", v1);
    printVector("Вектор v2", v2);

    printVector("Vector::Zero()", Vector::Zero());
    printVector("Vector::One()", Vector::One());

    Vector v_sum = v1 + v2;
    printVector("Сумма v1 + v2", v_sum);

    Number radius = v1.getValue_radius();
    Number angle = v1.getValue_angle();

    std::cout << "Для вектора v1:" << std::endl;
    std::cout << "  - Полярный радиус (длина): " << radius.getValue()
        << std::endl;
    std::cout << "  - Полярный угол (в радианах): " << angle.getValue()
        << std::endl;

    return 0;
}