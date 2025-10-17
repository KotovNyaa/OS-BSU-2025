#include "number.h"
#include <stdexcept>

const Number& Number::Zero() {
    static const Number zero_instance(0.0);
    return zero_instance;
}

const Number& Number::One() {
    static const Number one_instance(1.0);
    return one_instance;
}

Number::Number(double val) : number_(val) {}

double Number::getValue() const { return number_; }

Number& Number::operator+=(const Number& other) {
    number_ += other.number_;
    return *this;
}

Number& Number::operator-=(const Number& other) {
    number_ -= other.number_;
    return *this;
}

Number& Number::operator*=(const Number& other) {
    number_ *= other.number_;
    return *this;
}

Number& Number::operator/=(const Number& other) {
    if (other.number_ == 0.0) {
        throw std::runtime_error("Division by zero.");
    }
    number_ /= other.number_;
    return *this;
}

Number Number::operator+(const Number& other) const {
    Number temp = *this;
    temp += other;
    return temp;
}

Number Number::operator-(const Number& other) const {
    Number temp = *this;
    temp -= other;
    return temp;
}

Number Number::operator*(const Number& other) const {
    Number temp = *this;
    temp *= other;
    return temp;
}

Number Number::operator/(const Number& other) const {
    Number temp = *this;
    temp /= other;
    return temp;
}