/******************************************************************************
*******************************************************************************
       Name:  Andrew Serie & Sean Walter
 Assignment:  5 (Symmetric)
     Course:  CSc 456 Operating Systems
 Instructor:  Gamradt
*******************************************************************************
Description:  Performs a simple calculation for timing symmetric programming
*******************************************************************************
Usage:        ./a.out data.dat [times to loop 10,000 dataset]
******************************************************************************/

/* Preprocessor Directives */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>

/* User Defined Globals */
int DATA_SET_SIZE = 10000;

/* Function Declarations/Prototypes */
FILE * OpenFile(char *);
void FillArray(int * [], FILE *);
int Work(int);

/* Main Program Section */
int main(int argc, char **argv) {
	int *values = NULL;
	int *result = NULL;
	int maxLoop = 1;
	int i, j;
	FILE * f;
	double difference;
    struct timeval tvStart, tvEnd;

	/* Check for file */
	if (argc < 2) {
		perror("You must supply a filename.");
		exit(EXIT_FAILURE);
	}

	/* Get File and maxLoop */
	f = OpenFile(argv[1]);
	if (argc >= 3) maxLoop = atoi(argv[2]);

	printf("Running with a data size 10000 with %d loops.\n", maxLoop);

	/* Allocate Memory */
	values = (int*)malloc(DATA_SET_SIZE * sizeof(int));
	result = (int*)malloc(DATA_SET_SIZE * sizeof(int));

	/* Fill array */
	FillArray(&values, f);

	/* Do the work */
	/* start_t = clock(); */
	gettimeofday(&tvStart, NULL);
	for (i = 0; i < maxLoop; i++) {
		for (j = 0; j < DATA_SET_SIZE; j++)
			result[j] = Work(values[j]);
	}
	
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
   Function:  Work
*******************************************************************************
Description:  Performs the actual work function to time
*******************************************************************************
******************************************************************************/
int Work(int x) {
	return x == 0 ? 0 : 10;
}