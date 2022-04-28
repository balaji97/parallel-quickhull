#include "parallel_prefix_sum.h"
#include "seq_quickhull.h"

#define M 512

#pragma omp declare reduction(min_x: struct Point: omp_out = omp_in.x < omp_out.x ? omp_in : omp_out)
#pragma omp declare reduction(max_x: struct Point: omp_out = omp_in.x > omp_out.x ? omp_in : omp_out)
#pragma omp declare reduction(max_distance: struct Point: omp_out = omp_in.distance > omp_out.distance ? omp_in : omp_out)

void parallel_upper_hull(Point P[], bool convex_hull[], long n, Point l, Point r, long p=1) {
    if(n <= M) {
        upper_hull(P, convex_hull, n, l, r);
        return;
    }

    #pragma omp parallel for
    for(long i = 0; i < n; i++) {
        P[i].distance = P[i].distance_from_line(l, r);
    }

    Point farthest_point = P[0];

    #pragma omp parallel for reduction(max_distance:farthest_point)
    for(long i = 1; i < n; i++) {
        if(P[i].distance > farthest_point.distance) {
            farthest_point = P[i];
        }
    }

    convex_hull[farthest_point.index] = true;

    auto LU = new long[n];
    auto RU = new long[n];

    #pragma omp parallel for
    for(long i = 0; i < n; i++) {
        if(P[i].left(l, farthest_point)) {
            LU[i] = 1;
        } else {
            LU[i] = 0;
        }

        if(P[i].left(farthest_point, r)) {
            RU[i] = 1;
        } else {
            RU[i] = 0;
        }
    }

    parallel_prefix_sum(LU, n, p);
    parallel_prefix_sum(RU, n, p);

    long n_left_upper_points = LU[n-1];
    long n_right_upper_points = RU[n-1];

    auto left_upper_points = new Point[n_left_upper_points];
    auto right_upper_points = new Point[n_right_upper_points];

    #pragma omp parallel for
    for(long i = 0; i < n; i++) {
        if(LU[i] > 0 && (i == 0 || LU[i] > LU[i-1])) {
            left_upper_points[LU[i] - 1] = P[i];
        }

        if(RU[i] > 0 && (i == 0 || RU[i] > RU[i-1])) {
            right_upper_points[RU[i] - 1] = P[i];
        }
    }

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            parallel_upper_hull(left_upper_points, convex_hull, n_left_upper_points, l, farthest_point, p);
        }

        #pragma omp section
        {
            parallel_upper_hull(right_upper_points, convex_hull, n_right_upper_points, farthest_point, r, p);
        }
    }

    // garbage collection
    delete[] LU;
    delete[] RU;
    delete[] left_upper_points;
    delete[] right_upper_points;
}

void parallel_quickhull(Point P[], bool convex_hull[], long n, long p=1) {
    Point l = P[0], r = P[0];

    #pragma omp parallel for reduction(min_x:l)
    for(long i = 1; i < n; i++) {
        if(P[i].x < l.x) {
            l = P[i];
        }
    }

    #pragma omp parallel for reduction(max_x:r)
    for(long i = 1; i < n; i++) {
        if(P[i].x > r.x) {
            r = P[i];
        }
    }

    convex_hull[l.index] = true;
    convex_hull[r.index] = true;

    auto U = new long[n];
    auto L = new long[n];

    #pragma omp parallel for
    for(long i = 0; i < n; i++) {
        if(P[i].left(l, r)) {
            U[i] = 1;
        } else {
            U[i] = 0;
        }

        if(P[i].left(r, l)) {
            L[i] = 1;
        } else {
            L[i] = 0;
        }
    }

    parallel_prefix_sum(U, n, p);
    parallel_prefix_sum(L, n, p);

    long n_upper = U[n-1];
    long n_lower = L[n-1];

    auto upper_points = new Point[n_upper];
    auto lower_points = new Point[n_lower];

    #pragma omp parallel for
    for(long i = 0; i < n; i++) {
        if(U[i] > 0 && (i == 0 || U[i] > U[i-1])) {
            upper_points[U[i] - 1] = P[i];
        }

        if(L[i] > 0 && (i == 0 || L[i] > L[i-1])) {
            lower_points[L[i] - 1] = P[i];
        }
    }

    parallel_upper_hull(upper_points, convex_hull, n_upper, l, r, p);
    parallel_upper_hull(lower_points, convex_hull, n_lower, r, l, p);

    // garbage collection
    delete[] U;
    delete[] L;
    delete[] upper_points;
    delete[] lower_points;
}
