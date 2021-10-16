#include "point.hpp"

class Circle {
 private:
  Point center;
  const double radius;

 public:
  Circle(Point O, double r) : center(O), radius(r) {}
  void move(double dx, double dy);
  double intersectionArea(const Circle & otherCircle);
};
