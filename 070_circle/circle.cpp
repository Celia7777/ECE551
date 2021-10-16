#include "circle.hpp"

#include <cmath>

void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double bigradius;  //radius of the larger circle
  double smlradius;  //radius of the smaller circle
  double area_intersec;
  double dis_twocircl;  //distance between two centers

  bigradius = fmax(radius, otherCircle.radius);
  smlradius = fmin(radius, otherCircle.radius);
  dis_twocircl = center.distanceFrom(otherCircle.center);

  //the two circles don't have intersection
  if (dis_twocircl >= (bigradius + smlradius)) {
    area_intersec = 0;
    return area_intersec;
  }

  //the small circle within in the big circle
  else if ((dis_twocircl + smlradius) <= bigradius) {
    area_intersec = M_PI * std::pow(smlradius, 2);
    return area_intersec;
  }

  //the two circles have two intersection points
  else {
    double bigfan;  //area of the larger fan
    double smlfan;  //area of the smaller fan

    double arccos1 = std::acos(
        (std::pow(bigradius, 2) + std::pow(dis_twocircl, 2) - std::pow(smlradius, 2)) /
        (2 * bigradius * dis_twocircl));
    double arccos2 = std::acos(
        (std::pow(smlradius, 2) + std::pow(dis_twocircl, 2) - std::pow(bigradius, 2)) /
        (2 * smlradius * dis_twocircl));
    bigfan = arccos1 * std::pow(bigradius, 2);
    smlfan = arccos2 * std::pow(smlradius, 2);
    area_intersec = bigfan + smlfan - smlradius * dis_twocircl * std::sin(arccos2);

    return area_intersec;
  }
}
