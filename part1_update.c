/******************************************************************************
*******************************************************************************
       Name:  Andrew Serie & Sean Walter
 Assignment:  5
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
#include <time.h>

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
	clock_t start_t, end_t;
	double elapsed;

	/* Check for file */
	if (argc < 2) {
		perror("You must supply a filename.");
		exit(EXIT_FAILURE);
	}

	/* Get File and maxLoop */
	f = OpenFile(argv[1]);
	if (argc >= 3) maxLoop = atoi(argv[2]);

	printf("Running with a data size 10,000 with %d loops.\n", maxLoop);

	/* Allocate Memory */
	values = (int*)malloc(DATA_SET_SIZE * sizeof(int));
	result = (int*)malloc(DATA_SET_SIZE * sizeof(int));

	/* Fill array */
	FillArray(&values, f);

	/* Do the work */
	start_t = clock();
	for (i = 0; i < maxLoop; i++) {
		for (j = 0; j < DATA_SET_SIZE; j++)
			result[j] = Work(values[j]);
	}
	
	end_t = clock();
	elapsed = (double)(end_t - start_t) / CLOCKS_PER_SEC;

	printf("This took %f seconds to run.\n", elapsed); 
	fclose(f);
	return 0;
}

FILE * OpenFile(char * filename) {
	FILE * f;
	f = fopen(filename, "r");
	if (!f) {
		perror(filename);
		exit(EXIT_FAILURE);
	}
	return f;
}

void FillArray(int * values[], FILE * f) {
	int i;
	char intLine[25];
	for(i = 0; i < DATA_SET_SIZE; i++)
		(*values)[i] = atoi(fgets(intLine, 25, f));
	rewind(f);	/* Set stream location to 0 */
}

int Work(int x) {
	return x == 0 ? 0 : 10;
}