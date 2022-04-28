#include "point.h"
#include "math.h"

Point::Point(long x, long y, long index) {
    this->x = x;
    this->y = y;
    this->index = index;
    this->distance = 0;
}

Point::Point(){}

bool Point::left(Point p1, Point p2) const {
    return ((p2.x - p1.x)*(this->y - p1.y) - (p2.y - p1.y)*(this->x - p1.x)) > 0;
}

double Point::distance_from_point(Point p) const {
    return sqrt((this->x - p.x)*(this->x - p.x) + (this->y - p.y)*(this->y - p.y));
}

double Point::distance_from_line(Point p1, Point p2) const {
    return abs((p2.x - p1.x)*(p1.y - this->y) - (p1.x -this->x)*(p2.y - p1.y))/p1.distance_from_point(p2);
}
