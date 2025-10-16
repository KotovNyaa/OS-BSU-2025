#pragma once

#include "number.h"

class Vector {
private:
  Number val_x_;
  Number val_y_;

public:
  static const Vector &Zero();
  static const Vector &One();

  Vector();
  Vector(const Number &x, const Number &y);

  Number getValue_x() const;
  Number getValue_y() const;
  Number getValue_radius() const;
  Number getValue_angle() const;
  Vector &operator+=(const Vector &other);
  Vector operator+(const Vector &other) const;
};
