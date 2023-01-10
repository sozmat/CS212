#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int *AllocateArray(int N)
{
    /* Allocate an array with N integers.
     * The value of each element of the array should be a
     * random number between 0 and 10N.
     * Hint: use the rand() function and a modulo operator.
     */
	int *A = malloc(sizeof(int) * N);
	//iterate through array and give each int a random num
	for (int i = 0; i < N-1; i++){
		A[i] = rand() % 10*N;
	}
	return A;

}

void SortArray(int *A, int N)
{
    for(int i = 0; i < N-1; i++) {
	    for(int j = 1; j < N-1; j ++) {
		    if (A[j] < A[i]){
			    int tmp = A[i];
		    	    A[i] = A[j];
			    A[j] = tmp;}
	    }
    }
}

void DeallocateArray(int *A)
{
	free(A);
}

int main()
{
    int sizes[8] = { 1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000 };

/* For fun:
 *  int sizes[11] = { 1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000,
 *                    256000, 512000, 1024000 }; 
 */

    for (int i = 0 ; i < 8 ; i++)
    {
        double alloc_time = 0., sort_time = 0., dealloc_time = 0.;
        struct timeval startTime;
        struct timeval endTime;
	//AllocateArray()
	gettimeofday(&startTime, NULL);
	int *A = AllocateArray(sizes[i]);
	gettimeofday(&endTime, NULL);
	alloc_time = (endTime.tv_sec - startTime.tv_sec) +
		     (endTime.tv_usec - startTime.tv_usec) / 1000000.;		
        //SortArray()
	gettimeofday(&startTime, NULL);
	SortArray(A, sizes[i]);
	gettimeofday(&endTime, NULL);
	sort_time = (endTime.tv_sec - startTime.tv_sec) +
		    (endTime.tv_usec - startTime.tv_usec) / 1000000.;
	//DeallocateArray()
	gettimeofday(&startTime, NULL);
	DeallocateArray(A);
	gettimeofday(&endTime, NULL);
	dealloc_time = (endTime.tv_sec - startTime.tv_sec) +
		       (endTime.tv_usec - startTime.tv_usec) / 1000000.;

        printf("Timings for array of size %d\n", sizes[i]);
        printf("\tTime for allocation is %g, time per element = %g\n", alloc_time, alloc_time/sizes[i]);
        printf("\tTime for sort_time is %g, time per element = %g\n", sort_time, sort_time/sizes[i]);
        printf("\tTime for deallocation is %g\n", dealloc_time);
    }
}
