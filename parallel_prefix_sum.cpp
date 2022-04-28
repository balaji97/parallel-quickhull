#define M 128

void prefix_sum(long A[], long n, long start_index=0, long incr=1) {
    long i = start_index+incr;

    for(long ctr = 1; ctr < n; ctr++) {
        A[i] += A[i-incr];
        i += incr;
    }
}

void parallel_prefix_sum(long A[], long n, long p=1) {
    if(n <= p) {
        prefix_sum(A, n);
        return;
    }

    long m = n/p;

    #pragma omp parallel for
    for(long i = 0; i < p; i++) {
        long n_items = m;
        long start_index = i*m;

        if(i == p-1) {
            n_items = n - start_index;
        }

        prefix_sum(A, n_items, start_index);
    }

    prefix_sum(A, p-1, m-1, m);
    A[n-1] += A[(p-1)*m - 1];

    #pragma omp parallel for
    for(long i = 1; i < p; i++) {
        long n_items = m - 1;
        long start_index = i*m;

        if(i == p-1) {
            n_items = n - start_index - 1;
        }

        for(long j = start_index; j < start_index+n_items; j++) {
            A[j] += A[start_index-1];
        }
    }
}
