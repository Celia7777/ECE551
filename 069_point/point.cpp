#include "point.hpp"

#include <cmath>
#include <cstdio>

void Point::move(double dx, double dy) {
  x += dx;
  y += dy;
}

double Point::distanceFrom(const Point & p) {
  return std::sqrt(std::pow(x - p.x, 2) + std::pow(y - p.y, 2));
}
