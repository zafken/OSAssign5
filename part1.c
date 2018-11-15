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
#include <time.h>

int *y = NULL;



int main(int argc, char *argv[])
{
	clock_t start, end, actual;
	char fileName[25], ch;
	FILE *fp;
	int linecount = 0;
	int j = 0;
	int x;
	if (argc == 1)
	{
		printf("Enter the filename you wish to read\n");
		gets(fileName);
	}
	else
	{
		fileName = argv[1];
	}

	fp = fopen(fileName, "r");
	if (fp == NULL)
	{
		perror("Error while opening the file");
		exit(EXIT_FAILURE);
	}
	//get size of file
	while ((ch = fgetc(fp)) != EOF)
	{
		if (ch == '\n')
		{
			linecount++;
		}
	}

	y = (int*)malloc(linecount * sizeof(int));
	rewind(fp);
	start = clock();
	for (j = 0; j < linecount; j++)
	{
		x = atoi(fgets(fp));
		if (x == 0)
			y[j] = 0;
		else
			y[j] = 10;
	}
	end = clock();
	fclose(fp);


	total = (double)(end - start) / CLOCKS_PER_SEC;
	printf("This took %f seconds to run\n", total);
	return 0;
}