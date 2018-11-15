//part 1


#include <stdio.h>
#include <stdlib.h>


int *y = NULL;



void main(int argc, char *argv[])
{
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
	for (j = 0; j < linecount; j++)
	{
		x = atoi(fgets(fp));
		if (x == 0)
			y[j] = 0;
		else
			y[j] = 10;
	}
	fclose(fp);
}