# Overview
A parallel implementation of the Quickhull algorithm to find the convex hull of points on a plane. 

For an in-depth description of the algorithm, see the Project Report pdf file.

# Setup instructions

## Dependencies

* Install the latest version of the C++ compiler(g++)
* Install the latest version of OpenMP for parallelization

## Generating points

The program takes as input a list of points from a file. generate_points.cpp can be used to generate a random distribution of points to a file.

* Change the MIN, MAX and N_POINTS macros on generate_points.cpp to specify the distribution of points.
* Change the POINTS_FILE macro on generate_points.cpp to specify where to generate the points file

Compile and execute using 
```
g++ -o generate_points point.cpp generate_points.cpp
./generate_points
```

## Executing the program

You can modify the parameters in the main.cpp file.

* Change N_POINTS to specify the number of points to read from the file
* Change POINTS_FILE and HULL_FILE to specify the file from which to take the input, and the file to which to write the output convex hull
* Change the N_THREADS macro to specify the number of processors to use for the parallel computation.

In case you want to execute the program without OpenMP, you can comment out the following lines in main.cpp

```
#include "omp.h"
omp_set_num_threads(N_THREADS);
```

Compile and execute the program using:

```
g++ -o main point.cpp parallel_prefix_sum.cpp seq_quickhull.cpp parallel_quickhull.cpp main.cpp -fopenmp
./main
```

Omit the -fopenmp tag to compile and run without OpenMP.
