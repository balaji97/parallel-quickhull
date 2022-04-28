#include "fstream"
#include "random"
#include "point.h"

#define MIN -1000
#define MAX 1000
#define N_POINTS 100000
#define POINTS_FILE "/Users/balajijayasankar/Desktop/paralell_project/parallel_quickhull/data/points.txt"

void generate_uniform_points(Point P[], long n) {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<long> uni(MIN, MAX);

    for(long i = 0; i < n; i++) {
        P[i] = Point(uni(rng), uni(rng) ,i);
    }
}

int main() {
    Point P[N_POINTS];
    generate_uniform_points(P, N_POINTS);

    std::ofstream points_file(POINTS_FILE);

    for(long i = 0; i < N_POINTS; i++) {
        points_file<<P[i].x<<" "<<P[i].y<<"\n";
    }

    return 0;
}
