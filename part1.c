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
	char line[25];
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
	rewind(fp);
	start = clock();
	for (j = 0; j < linecount; j++)
	{
		x = atoi(fgets(line, 25, fp));
		if (x == 0)
			y[j] = 0;
		else
			y[j] = 10;
	}
	end = clock();
	fclose(fp);


	actual = (double)(((end - start)*1000) / CLOCKS_PER_SEC);
	printf("This took %f milliseconds to run\n", actual);
	return 0;
}