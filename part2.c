//part 2


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 4
int *y = NULL;
int *numbers = NULL;
pthread_t tid[NUM_THREADS];
int linecount;


int main(int argc, char *argv[])
{
	clock_t start, end, actual;
	char fileName[25], ch;
	FILE *fp;
	int j = 0;
	int x;
	int scope;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	linecount = 0;
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
	rewind(fp);
	y = (int*)malloc(linecount * sizeof(int));
	numbers = (int*)malloc(linecount * sizeof(int));
	for (j = 0; j < linecount; j++)
	{
		numbers[j] = atoi(fgets(fp));
	}
	if (pthread_attr_getscope(&attr, &scope) != 0)
		fprintf(stderr, "Unable to get scheduling scope\n");
	else
	{
		if (scope == PTHREAD_SCOPE_PROCESS)
			printf("PTHREAD_SCOPE_PROCESS");
		else if (scope == PTHREAD_SCOPE_SYSTEM)
			printf("PTHREAD_SCOPE_SYSTEM");
		else
			fprintf(stderr, "Illegal scope value.\n");
	}
	pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
	start = clock();
	for (j = 0; j < NUM_THREADS; j++)
		pthread_create(&tid[i], &attr, algorithm, NULL);
	for (j = 0; j < NUM_THREADS; j++)
		pthread_join(tid[i], NULL);
	end = clock();
	fclose(fp);

	total = (double)(end - start) / CLOCKS_PER_SEC;
	printf("This took %f seconds to run\n", total);
	return 0;

}


void *algorithm(void *param)
{
	int j, MAX, MIN;
	if (pthread_self() == tid[0])
	{
		MAX = linecount / 4;
		MIN = 0;
	}
	else if(pthread_self() == tid[1])
	{
		MAX = linecount / 2;
		MIN = linecount / 4;
	}
	else if (pthread_self() == tid[2])
	{
		MAX = (linecount * 3) / 4;
		MIN = linecount / 2;
	}
	else
	{
		MAX = linecount;
		MIN = (linecount * 3) / 4;
	}
		
	for (j = MIN; j < MAX; j++)
	{
		
		if (numbers[j] == 0)
			y[j] = 0;
		else
			y[j] = 10;
	}
	pthread_exit(0);
}