#include "vector.h"
#include <cmath>

const Vector& Vector::Zero() {
	static const Vector zero_instance(Number::Zero(), Number::Zero());
	return zero_instance;
}

const Vector& Vector::One() {
	static const Vector one_instance(Number::One(), Number::One());
	return one_instance;
}

Vector::Vector() : val_x_(), val_y_() {}

Vector::Vector(const Number& x, const Number& y) : val_x_(x), val_y_(y) {}

Number Vector::getValue_x() const { return val_x_; }
Number Vector::getValue_y() const { return val_y_; }

Number Vector::getValue_radius() const {
	double x = val_x_.getValue();
	double y = val_y_.getValue();
	return Number(std::sqrt(x * x + y * y));
}

Number Vector::getValue_angle() const {
	double x = val_x_.getValue();
	double y = val_y_.getValue();
	return Number(std::atan2(y, x));
}

Vector& Vector::operator+=(const Vector& other) {
	this->val_x_ += other.val_x_;
	this->val_y_ += other.val_y_;
	return *this;
}

Vector Vector::operator+(const Vector& other) const {
	Vector temp = *this;
	temp += other;
	return temp;
}