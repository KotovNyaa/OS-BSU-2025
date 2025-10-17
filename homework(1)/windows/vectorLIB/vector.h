#pragma once

#ifdef VECTORLIB_EXPORTS
#define VECTORLIB_API __declspec(dllexport)
#else
#define VECTORLIB_API __declspec(dllimport)
#endif

#include "../NumberLib/Number.h"

class VECTORLIB_API Vector {
private:
	Number val_x_;
	Number val_y_;

public:
	static const Vector& Zero();
	static const Vector& One();

	Vector();
	Vector(const Number& x, const Number& y);

	Number getValue_x() const;
	Number getValue_y() const;
	Number getValue_radius() const;
	Number getValue_angle() const;
	Vector& operator+=(const Vector& other);
	Vector operator+(const Vector& other) const;
};