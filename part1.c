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
int *numbers = NULL;


int main(int argc, char *argv[])
{
	char line[25];
	clock_t start, end;
	double actual;
	char fileName[25], ch;
	FILE *fp;
	int linecount = 0;
	int j = 0;
	int x;
	if (argc == 1)
	{
		printf("Enter the filename you wish to read\n");
		gets(fileName);
		fp = fopen(fileName, "r");
	}
	else
	{
		fp = fopen(argv[1], "r");

	}

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
	numbers = (int*)malloc(linecount * sizeof(int));
	rewind(fp);
	for (j = 0; j < linecount; j++)
	{
		numbers[j] = atoi(fgets(line, 25, fp));
	}
	start = clock();
	for (j = 0; j < linecount; j++)
	{

		if (numbers[j] == 0)
			y[j] = 0;
		else
			y[j] = 10;
	}
	end = clock();
	fclose(fp);


	actual = ((end - start) / (double)CLOCKS_PER_SEC) * 1000;
	printf("This took %f milliseconds to run\n", actual);
	return 0;
}