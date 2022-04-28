//
// Created by Balaji Jayasankar on 4/18/22.
//

#ifndef PARALLEL_QUICKHULL_POINT_H

struct Point {
    long x, y, index;
    double distance;

    Point(long x, long y, long index);

    Point();

    bool left(Point p1, Point p2) const;

    double distance_from_point(Point p) const;

    double distance_from_line(Point p1, Point p2) const;
};

#define PARALLEL_QUICKHULL_POINT_H

#endif //PARALLEL_QUICKHULL_POINT_H
