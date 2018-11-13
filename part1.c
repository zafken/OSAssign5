//part 1

int *y = NULL;



void main()
{
	int MAX = 50;
	int j = 0;
	int x;
	y = (int*)malloc(MAX*sizeof(int));

	for (j = 0; j < MAX; j++)
	{
		printf("Enter an integer value: ");
		scanf("%d", &x);
		if (x == 0)
			y[j] = 0;
		else
			y[j] = 10;
	}
}