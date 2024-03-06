/*  main.c file
    Aaron Heishman
    Systems I
    Lab 4 - Thread Level Parallelism
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <pthread.h>
/* Sizes for each matrix */
#define A_ROWS 1200
#define A_COLS 1000
#define B_COLS 500
/* Global Vars */
int matrix_A[A_ROWS][A_COLS];
int matrix_B[A_COLS][B_COLS];
int matrix_C[A_ROWS][B_COLS];
int *thread_ranges;
double *thread_runtimes;

/* Initializes Matrix A and Matrix B */
void initialize_matrices() {
    int row, column;
    // initialize matrix a
    for (row = 0; row < A_ROWS; row++) {
        for (column = 0; column < A_COLS; column++) {
            matrix_A[row][column] = row + column; 
        }
    }
    // Initialize matrix b
    for (row = 0; row < A_COLS; row++) {
        for (column = 0; column < B_COLS; column++) {
            matrix_B[row][column] = row + column;
        }
    }
}

/* Multiply Matrices matrix_A with Matrices matrix_B to Produce matrix_C */
void *multiply_matrices(void *param) {
    /* ID is used to figure out the job assignment of the thread before multiplying */
    int *thread_id = (int *)param;
    int start_row = thread_ranges[*thread_id], end_row = thread_ranges[*thread_id + 1];
    int i, j, k;
    struct timespec begin, finish;
    /* Get start time */
    clock_gettime(CLOCK_MONOTONIC, &begin);
    /*  */
    for (i = start_row; i < end_row; i++) {
        for (j = 0; j < B_COLS; j++) {
            matrix_C[i][j] = 0;
            for (k = 0; k < A_COLS; k++) {
                matrix_C[i][j] += matrix_A[i][k] * matrix_B[k][j];
            }
        }
    }
    /* Get End time */
    clock_gettime(CLOCK_MONOTONIC, &finish);
    /* Calculate resulting runtime*/
    double result = (finish.tv_sec - begin.tv_sec);
    result += (finish.tv_nsec - begin.tv_nsec) / 1e9;
    thread_runtimes[*thread_id] = result; // store each thread runtime at the index with the same id as the thread
    return thread_id;
}

/* 
    Checks to make sure the argument count is correct
    Printing an error and exiting if the argument is falls
 */
void check_args_count(int argc) {
    if (argc != 2) {
        fprintf(stderr, "ERROR: You must enter only one argument.\n");
        fprintf(stderr, "Usage: $<prorgram name> <integer>\n");
        exit(1);
    }
}
/* 
    Check argument entered is within the range [1,5] and return said
    value as an int, otherwise prints an error.
*/
int check_arg_validity(char *arg) {
    char *end_ptr;
    const int MAX = 5, MIN = 1, BASE = 10;
    int val = (int)strtol(arg, &end_ptr, BASE);
    if (val < MIN || val > MAX) {
        fprintf(stderr, "ERROR: <%s> is out of range.\n", arg);
        fprintf(stderr, "Usage: Value must be in the range [1, 5]\n");
        exit(1);
    }
    return val;
}

/* Prints the thread times and any errors that my happen */
void print_output(int thread_count, int *thread_error_count) {
    int i;
    /* Print output */
    printf("Threads Seconds Errors\n");
    for (i = 0; i < thread_count; i++) {
        printf("%d\t%.2lf\t", (i+1), thread_runtimes[i]);
        if (thread_error_count[i] > 0) {
            printf("%d Errors\n", thread_error_count[i]);
        } else {
            printf("No Errors\n");
        }
    }
}

/* Main */
int main(int argc, char* argv[]) {
    /* Validation checks */
    check_args_count(argc);
    int thread_count = check_arg_validity(argv[1]);
    /* Program set up */
    const int jobs_per_thread = A_ROWS / thread_count; // amount of jobs each thread will do
    int return_code; // used for error checks
    int *thread_ids; // array to hold thread_ids
    int i; // index tracker 
    int thread_error_count[thread_count];
    /* pthread vars */
    pthread_t workers[thread_count];
    pthread_attr_t attr;
    /* Initialize global variables, matrices, etc */
    initialize_matrices(); // initialize matrice A and B
    return_code = pthread_attr_init(&attr);
    assert(return_code == 0);
    /* allocate memory for worker id array */
    thread_ids = (int*)malloc(thread_count * sizeof(int));
    assert(thread_ids != NULL);
    memset(thread_ids, 0, thread_count * sizeof(int));
    /* allocate memory for the thread_ranges array */
    thread_ranges = (int*)malloc((thread_count+1) * sizeof(int));
    assert(thread_ranges != NULL);
    memset(thread_ranges, 0, thread_count * sizeof(int));
    /* allocate memory for the thread_time array*/
    thread_runtimes = (double*)malloc(thread_count*sizeof(double));
    assert(thread_runtimes != NULL);
    memset(thread_runtimes, 0, thread_count * sizeof(double));
    /* initialize thread error count with 0 */
    memset(thread_error_count, 0, thread_count * sizeof(int));
    
    /* create job order */
    for (i = 0; i < thread_count + 1; i++) {
        /* calculate total jobs per thread and add to assignment array*/
        thread_ranges[i] = jobs_per_thread * i;
        if (i < thread_count) { 
            thread_ids[i] = i; /* set id for each worker */
        }
    }
    /* create worker threads */
    for (i = 0; i < thread_count; i++) {
        return_code = pthread_create(&workers[i], &attr, multiply_matrices, (void *) &thread_ids[i]);
        if (return_code != 0) {
            thread_error_count[i] += 1;
        }
    }
    /* join each thread */
    void *thread_id;
    for (i = 0; i < thread_count; i++) {
        return_code = pthread_join(workers[i], &thread_id);
        if (return_code != 0) {
            thread_error_count[i] += 1;
        } 
    }
    /* print finished output */
    print_output(thread_count, thread_error_count);
    /* free memory */
    return_code = pthread_attr_destroy(&attr);
    assert(return_code==0);
    free(thread_ids);
    free(thread_ranges);
    free(thread_runtimes);
    return 0;
}