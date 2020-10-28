#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX 50

typedef struct
{
	char FirstName[30];
	char LastName[30];
	int Grade;
}studenti;

int count(const char* file)
{
	int counter = 0;
	char c[100];

	FILE *f = NULL;
	f = fopen(file, "r");
	if (f == NULL)
	{
		printf("Mistake!!");
		return -1;
	}

	while (fgets(c,100,f) != EOF)
	{
			counter++;
	}
	return counter;
}
int print(int num, const char* file)
{
	int i;
	FILE *f;
	f = fopen(file, "r");
	if (f == NULL)
	{
		printf("Mistake!!");
		return -2;
	}
	studenti *s;
	s = (studenti *)malloc(num * sizeof(studenti));

	for (i = 0; i < num; i++)
	{
		fscanf(f, "%s", (s + i)->FirstName);
		fscanf(f, "%s", (s + i)->LastName);
		fscanf(f, "%d", &(s + i)->Grade);
		fgetc(f);
	}
	for (i = 0; i < num; i++)
	{
		printf("%s\t%s\t%d\t%.2f\n", (s + i)->FirstName, (s + i)->LastName, (s + i)->Grade,((float)(s+i)->Grade)/MAX *100);
	}

	return 0;
}

int main()
{
	int num;

	FILE *f = NULL;
	f = fopen("TextFile2.txt", "r");

	if (f == NULL)
	{
		printf("Mistake!!");
		return 1;
	}

	num = count("TextFile2.txt");

	printf("RESULTS:\n");
	print(num, "TextFile2.txt");

}