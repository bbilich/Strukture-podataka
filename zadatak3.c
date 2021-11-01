#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX 50

struct _Person;
typedef struct _Person* Position;
typedef struct _Person
{
	char FirstName[MAX];
	char LastName[MAX];
	int BirthYear;
	Position Next;
}Person;

int PrependList(Position P);
int PrintList(Position P);
Position CreatePerson(char* name, char* surname, int year);
int AppendList(Position P);
Position FindByLastName(char* surname, Position P);
int EraseElement(char* surname, Position P);
Position FindPrevious(char* surname, Position P);
int InsertAfter(char* surname, Position P);
int InsertBefore(char* surname, Position P);
int WriteInFile(char* fileName, Position P);
int ReadFromFile(char* fileName);
int Sorting(char* name, char* surname, int year, Position P);
int DeleteAll(Position P);
int Pointers(Position P,Position Q);

int main()
{
	Person Head;
	Head.Next = NULL;

	/*PrependList(&Head);
	PrependList(&Head);
	AppendList(&Head);
	PrintList(Head.Next);
	EraseElement("Bilic", &Head);
	PrintList(Head.Next);
	InsertAfter("Milic", &Head);
	InsertBefore("Milic", &Head);*/

	for (int i = 0; i < 5; i++)
	{
		PrependList(&Head);
	}
	
	PrintList(Head.Next);

	WriteInFile("File.txt", Head.Next);
	ReadFromFile("File.txt");

	DeleteAll(&Head);
	PrintList(Head.Next);

	return EXIT_SUCCESS;
}

Position CreatePerson(char* name, char* surname, int year)
{
	Position Q = NULL;
	Q = (Position)malloc(sizeof(Person));

	if (NULL == Q)
	{
		perror("Cannot allocate memory!\n");
		return NULL;
	}

	strcpy(Q->FirstName, name);
	strcpy(Q->LastName, surname);
	Q->BirthYear = year;
	Q->Next = NULL;

	return Q;
}

int PrependList(Position P)
{
	char name[MAX], surname[MAX];
	int year;

	printf("Enter name: ");
	scanf("%s", name);
	printf("Enter surname: ");
	scanf("%s", surname);
	printf("Enter birth year: ");
	scanf("%d", &year);

	Sorting(name, surname, year, P);

	return EXIT_SUCCESS;
}

int AppendList(Position P)
{
	while (P->Next != NULL)
		P = P->Next;

	if (NULL == P->Next)
		PrependList(P);

	return EXIT_SUCCESS;
}

int PrintList(Position P)
{
	if (P == NULL)
	{
		printf("List is empty!\n");
		return -1;
	}

	else
	{
		printf("\n\n******LIST OF STUDENTS******\n");
		printf("FIRST NAME\tLAST NAME\tBIRTH YEAR\n");
		while (P != NULL)
		{
			printf("%s\t\t%s\t\t%d\n", P->FirstName, P->LastName, P->BirthYear);
			P = P->Next;
		}
		printf("\n\n");

		return EXIT_SUCCESS;
	}
}

Position FindByLastName(char* surname, Position P)
{
	while (P != NULL && strcmp(P->LastName, surname))
		P = P->Next;
	return P;
}

Position FindPrevious(char* surname, Position P)
{
	Position previous;
	previous = P;
	P = P->Next;

	while (P != NULL && strcmp(P->LastName, surname) != 0)
	{
		previous = P;
		P = P->Next;
	}

	if (NULL == P)
	{
		printf("That element of list does not exist!\n");
		return NULL;
	}

	else
		return previous;
}

int EraseElement(char* surname, Position P)
{
	Position temp = NULL;
	P = FindPrevious(surname, P);
	if (NULL == P)
	{
		printf("Could not find that element of a list!\n");
		return -1;
	}

	else
	{
		temp = P->Next;
		P->Next = temp->Next;
		free(temp);
	}

	return EXIT_SUCCESS;
}

int InsertAfter(char* surname, Position P)
{
	Position Q;
	Q = FindByLastName(surname, P->Next);
	PrependList(Q);

	if (NULL == Q)
	{
		printf("Could not find that element of a list!\n");
		return -1;
	}

	return EXIT_SUCCESS;
}

int InsertBefore(char* surname, Position P)
{
	Position Q;
	Q = FindPrevious(surname, P);
	PrependList(Q);

	if (NULL == Q)
	{
		printf("Could not find that element of a list!\n");
		return -1;
	}

	return EXIT_SUCCESS;
}

int WriteInFile(char* fileName, Position P)
{
	FILE* file = NULL;
	file = fopen(fileName, "w");

	if (NULL == file)
	{
		printf("Could not open the file!\n");
		return -1;
	}

	while (P != NULL)
	{
		fprintf(file, "Person %s %s was born in %d.\n", P->FirstName, P->LastName, P->BirthYear);
		P = P->Next;
	}

	fclose(file);
	return EXIT_SUCCESS;
}


int ReadFromFile(char* fileName)
{
	FILE* file = NULL;
	char buffer[1024] = { 0 };
	file = fopen(fileName, "r");

	if (NULL == file)
	{
		printf("Could not open the file!\n");
		return -1;
	}


	while (fgets(buffer, 1024, file) != NULL)
		puts(buffer);

	return EXIT_SUCCESS;
}

int DeleteAll(Position P)
{
	Position temp = NULL;
	while (P->Next != NULL)
	{
		temp = P->Next;
		P->Next = temp->Next;
		free(temp);
	}
	return 0;
}

int Pointers(Position P, Position Q)
{
	Q->Next = P->Next;
	P->Next = Q;

	return EXIT_SUCCESS;
}

int Sorting(char* name, char* surname, int year, Position P)
{
	Position Q = CreatePerson(name, surname, year);

	while (P->Next != NULL && strcmp(P->Next->LastName, surname) < 0)
		P = P->Next;

	if (P->Next != NULL)
	{
		if (strcmp(P->Next->LastName, surname) > 0)
			Pointers(P, Q);
		else
		{
			while (P->Next != NULL && strcmp(P->Next->FirstName, name) < 0)
				P = P->Next;
			if (P->Next != NULL)
			{
				Pointers(P, Q);
				return EXIT_SUCCESS;
			}
			else
			{
				return -1;
			}
		}
	}
	else
		Pointers(P, Q);
	
}

