#pragma once

class Number {
private:
	double number_;

public:
	static const Number& Zero();
	static const Number& One();

	explicit Number(double val = 0.0);

	double getValue() const;

	Number& operator+=(const Number& other);
	Number& operator-=(const Number& other);
	Number& operator*=(const Number& other);
	Number& operator/=(const Number& other);

	Number operator+(const Number& other) const;
	Number operator-(const Number& other) const;
	Number operator*(const Number& other) const;
	Number operator/(const Number& other) const;
};