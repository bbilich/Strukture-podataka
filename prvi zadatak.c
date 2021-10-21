#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_SIZE (120)
#define MAX_LINE (1024)

typedef struct _student
{
	char FirstName[MAX_SIZE];
	char LastName[MAX_SIZE];
	double num;

}student;

int ReadFromFile(char* FileName);
student* MemoryAllocation_ReadStudents(int num, char* FileName);

int main()
{
	int count = 0;
	double relative;
	student* student_ = NULL;
	FILE* File = NULL;

	File = fopen("TextFile1.txt", "r");
	if (!File)
	{
		printf("Error!");
		return -2;
	}

	count = ReadFromFile("TextFile1.txt");
	student_ = MemoryAllocation_ReadStudents(count, "TextFile1.txt");

	double max = student_[0].num;

	for (int i = 0; i < count; i++)
	{
		if (student_[i].num > max)
			max = student_[i].num;
	}

	printf("REZULTATI:\n");
	printf("IME\tPREZIME\tREL.BR.BOD.\tAPS.BR.BOD.\n");
	for (int i = 0; i < count; i++)
	{
		relative = student_[i].num / max * 100;
		printf("%s\t%s\t%.2lf\t\t%.2lf\n", student_[i].FirstName, student_[i].LastName, student_[i].num,relative);
		relative = 0;
	}
	
	fclose(File);
	return 0;
}

int ReadFromFile(char* FileName)
{
	FILE* file = NULL;
	int counter = 0;
	char buffer[MAX_LINE] = { 0 };

	file = fopen(FileName, "r");
	if (!file) {
		printf("Error!");
		return -1;
	}
	while (!feof(file))
	{
		fgets(buffer, MAX_LINE, file);
		counter++;
	}

	fclose(file);

	return counter;
}

student* MemoryAllocation_ReadStudents(int num, char* FileName)
{
	FILE* file = NULL;
	int counter = 0;
	student* students = NULL;

	students = (student*)malloc(num * sizeof(student));
	file = fopen(FileName, "r");
	if (!file) {
		printf("Error!");
		free(students);
		return NULL;
	}
	while (!feof(file))
	{
		fscanf(file, " %s %s %lf", students[counter].FirstName, students[counter].LastName, &students[counter].num);
		counter++;
	}

	fclose(file);

	return students;
}
