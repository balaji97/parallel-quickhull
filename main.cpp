#include "fstream"
#include "parallel_quickhull.h"
#include "seq_quickhull.h"
#include "iostream"
#include "chrono"
//#include "omp.h"

using std::cout;

#define N_POINTS 100000
#define N_THREADS 8
#define POINTS_FILE "/Users/balajijayasankar/Desktop/paralell_project/parallel_quickhull/data/points.txt"
#define HULL_FILE "/Users/balajijayasankar/Desktop/paralell_project/parallel_quickhull/data/hull.txt"

int main() {
    //omp_set_num_threads(256);
    Point *P[N_POINTS];

    std::ifstream points_file(POINTS_FILE);
    std::ofstream hull_file(HULL_FILE);

    cout<<"Reading input\n";
    for(long i = 0; i < N_POINTS; i++) {
        long x, y;
        points_file>>x>>y;

        P[i] = new Point(x, y, i);
    }

    bool convex_hull[N_POINTS];
    for(bool & i : convex_hull) {
        i = false;
    }

    cout<<"Finding quickhull\n";
    auto start = std::chrono::high_resolution_clock::now();
    parallel_quickhull(P, convex_hull, N_POINTS, N_THREADS);
    //quick_hull(P, convex_hull, N_POINTS);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    cout<<"Time taken "<<duration.count()<<" milliseconds\n";

    cout<<"Writing output\n";
    for(long i = 0; i < N_POINTS; i++) {
        if(convex_hull[i]) {
            hull_file<<P[i]->x<<" "<<P[i]->y<<"\n";
        }
    }

    return 0;
}