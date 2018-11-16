/******************************************************************************
*******************************************************************************
       Name:  Andrew Serie & Sean Walter
 Assignment:  5
     Course:  CSc 456 Operating Systems
 Instructor:  Gamradt
*******************************************************************************
Description:  
*******************************************************************************
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/* Preprocessor Directives */

/* Function Declarations/Prototypes */
FILE * OpenFile(char *);
int GetMaxSize(FILE *);
int Work(int);

/* Main Program Section */
int main(int argc, char **argv) {
	char intLine[25];
	int *values = NULL;
	int maxSize = -1;
	int i;
	FILE * f;
	clock_t start_t, end_t;
	double elapsed;

	/* Check for file */
	if (argc < 2) {
		perror("You must supply a filename.");
		exit(EXIT_FAILURE);
	}

	/* Get File and maxSize */
	f = OpenFile(argv[1]);
	if (argc < 3) maxSize = GetMaxSize(f);
	else maxSize = atoi(argv[2]);

	/* Allocate Memory */
	values = (int*)malloc(maxSize * sizeof(int));

	/* Do the work */
	start_t = clock();
	for (i = 0; i < maxSize; i++)
		values[i] = Work(atoi(fgets(intLine, 25, f)));
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

int GetMaxSize(FILE * f) {
	char ch;
	int count = 0;
	while ((ch = fgetc(f)) != EOF) {
		if (ch == '\n') count++;
	}
	rewind(f);	/* Set stream location to 0 */
	return count;
}

int Work(int x) {
	return x == 0 ? 0 : 10;
}