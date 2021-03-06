/******************************************************************************
*******************************************************************************
       Name:  Andrew Serie & Sean Walter
 Assignment:  5 (Parallel)
     Course:  CSc 456 Operating Systems
 Instructor:  Gamradt
*******************************************************************************
Description:  Performs a simple calculation for timing parallel programming
*******************************************************************************
Usage:        ./a.out data.dat [times to loop 10,000 dataset]
******************************************************************************/

/* Preprocessor Directives */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>
#define NUM_THREADS 4

/* User Defined Globals */
int DATA_SET_SIZE = 10000;
int *values = NULL;
int *result = NULL;
pthread_t tid[NUM_THREADS];
int maxLoop = 1;

/* Function Declarations/Prototypes */
FILE * OpenFile(char *);
void FillArray(int * [], FILE *);
void * Algorithm(void *);
int Work(int);

/* Main Program Section */
int main(int argc, char **argv) {
	int j;
	FILE * f;
    double difference;
    struct timeval tvStart, tvEnd;
    pthread_attr_t tattr;
    
	/* Check for file */
	if (argc < 2) {
		perror("You must supply a filename.");
		exit(EXIT_FAILURE);
	}

	/* Get File and maxLoop */
	f = OpenFile(argv[1]);
	if (argc >= 3) maxLoop = atoi(argv[2]);

	printf("Running data size 10000 with %d loops.\n", maxLoop);

	/* Allocate Memory */
	values = (int*)malloc(DATA_SET_SIZE * sizeof(int));
	result = (int*)malloc(DATA_SET_SIZE * sizeof(int));

	/* Fill array */
	FillArray(&values, f);

    /* Handle Thread Scope */
    pthread_attr_init(&tattr);
	pthread_attr_setscope(&tattr, PTHREAD_SCOPE_SYSTEM);

	/* Do the thread work */
    gettimeofday(&tvStart, NULL);
    for (j = 0; j < NUM_THREADS; j++)
        pthread_create(&tid[j], &tattr, Algorithm, NULL);
    for (j = 0; j < NUM_THREADS; j++)
        pthread_join(tid[j], NULL);

    gettimeofday(&tvEnd, NULL);
    difference = (tvEnd.tv_sec - tvStart.tv_sec)*1000000;
    difference = (difference + tvEnd.tv_usec - tvStart.tv_usec)/1000000;
	printf("== %f sec ==\n", difference); 

	fclose(f);
	return 0;
}

/******************************************************************************
*******************************************************************************
   Function:  OpenFile
*******************************************************************************
Description:  Opens a file for reading
*******************************************************************************
******************************************************************************/
FILE * OpenFile(char * filename) {
	FILE * f;
	f = fopen(filename, "r");
	if (!f) {
		perror(filename);
		exit(EXIT_FAILURE);
	}
	return f;
}

/******************************************************************************
*******************************************************************************
   Function:  FillArray
*******************************************************************************
Description:  Fills array with data that was given from file
*******************************************************************************
******************************************************************************/
void FillArray(int * values[], FILE * f) {
	int i;
    char intLine[25];
	for(i = 0; i < DATA_SET_SIZE; i++)
		(*values)[i] = atoi(fgets(intLine, 25, f));
	rewind(f);	/* Set stream location to 0 */
}

/******************************************************************************
*******************************************************************************
   Function:  Algorithm
*******************************************************************************
Description:  Performs the looping through data and calling work
*******************************************************************************
******************************************************************************/
void *Algorithm(void *param)
{
	int i, j, MIN, MAX;
	if (pthread_self() == tid[0]) {
        MIN = 0;
		MAX = DATA_SET_SIZE / 4;
	}
	else if(pthread_self() == tid[1]) {
        MIN = (DATA_SET_SIZE / 4) + 1;
		MAX = DATA_SET_SIZE / 2;
	}
	else if (pthread_self() == tid[2]) {
        MIN = (DATA_SET_SIZE / 2) + 1;
		MAX = (DATA_SET_SIZE * 3) / 4;
	}
	else {
        MIN = ((DATA_SET_SIZE * 3) / 4) + 1;
		MAX = DATA_SET_SIZE;
	}
	
    for (i = 0; i < maxLoop; i++) {
        for (j = MIN; j < MAX; j++)
            result[j] = Work(values[j]);
    }
	pthread_exit(0);
}

/******************************************************************************
*******************************************************************************
   Function:  Work
*******************************************************************************
Description:  Performs the actual work function to time
*******************************************************************************
******************************************************************************/
int Work(int x) {
	return x == 0 ? 0 : 10;
}