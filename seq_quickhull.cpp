#include <iostream>
#include "point.h"

long count_points_on_left(Point *P[], long n, Point l, Point r) {
    long n_points_on_left = 0;

    for(long i = 0; i < n; i++) {
        if(P[i]->left(l, r)) {
            n_points_on_left += 1;
        }
    }

    return n_points_on_left;
}

void get_points_on_left(Point *P[], long n, Point l, Point r, Point *points_on_left[]) {
    long index = 0;

    for(long i = 0; i < n; i++) {
        if(P[i]->left(l, r)) {
            points_on_left[index++] = P[i];
        }
    }
}

long find_farthest_point(Point *P[], long n, Point l, Point r) {
    long farthest_point = -1;
    double max_distance = -1;

    for(long i = 0; i < n; i++) {
        if(P[i]->distance_from_line(l, r) > max_distance) {
            farthest_point = i;
            max_distance = P[i]->distance_from_line(l, r);
        }
    }

    return farthest_point;
}

void upper_hull(Point *P[], bool convex_hull[], long n, Point l, Point r) {
    if(n == 0) {
        return;
    }

    Point farthest_point = *P[find_farthest_point(P, n, l, r)];

    convex_hull[farthest_point.index] = true;

    long n_left_upper_points = count_points_on_left(P, n, l, farthest_point);
    long n_right_upper_points = count_points_on_left(P, n, farthest_point, r);

    auto left_upper_points = new Point*[n_left_upper_points];
    auto right_upper_points = new Point*[n_right_upper_points];

    get_points_on_left(P, n, l, farthest_point, left_upper_points);
    get_points_on_left(P, n, farthest_point, r, right_upper_points);

    upper_hull(left_upper_points, convex_hull, n_left_upper_points, l, farthest_point);
    upper_hull(right_upper_points, convex_hull, n_right_upper_points, farthest_point, r);

    // garbage collection
    delete[] left_upper_points;
    delete[] right_upper_points;
}

void quick_hull(Point *P[], bool convex_hull[], long n) {
    Point l = *P[0], r = *P[0];

    for(long i = 0; i < n; i++) {
        if(P[i]->x <= l.x) {
            l = *P[i];
        }

        if(P[i]->x >= r.x) {
            r = *P[i];
        }
    }

    convex_hull[l.index] = true;
    convex_hull[r.index] = true;

    long n_upper = count_points_on_left(P, n, l, r);
    long n_lower = count_points_on_left(P, n, r, l);

    auto *upper_points = new Point*[n_upper];
    auto *lower_points = new Point*[n_lower];

    get_points_on_left(P, n, l, r, upper_points);
    get_points_on_left(P, n, r, l, lower_points);

    upper_hull(upper_points, convex_hull, n_upper, l, r);
    upper_hull(lower_points, convex_hull, n_lower, r, l);

    // garbage collection
    delete[] upper_points;
    delete[] lower_points;
}
