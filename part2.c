//part 2


#include <stdio.h>
#include <stdlib.h>


int *y = NULL;



void main()
{
	char fileName[25], ch;
	FILE *fp;
	int linecount = 0;
	int MAX = 0;
	int j = 0;
	int x;
	printf("Enter the filename you wish to read\n");
	gets(fileName);

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

	y = (int*)malloc( linecount * sizeof(int));
	rewind(fp);
	for (j = 0; j < linecount; j++)
	{
		x = atoi(fgets(fp));
		if (x == 0)
			y[j] = 0;
		else
			y[j] = 10;
	}
}