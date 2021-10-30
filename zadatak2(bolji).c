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

int main()
{
	Person Head;
	Head.Next = NULL;

	PrependList(&Head);
	PrependList(&Head);
	AppendList(&Head);
	PrintList(Head.Next);
	EraseElement("Bilic", &Head);
	PrintList(Head.Next);

	return EXIT_SUCCESS;
}

Position CreatePerson(char* name,char* surname,int year)
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
	Position Q;
	char name[MAX], surname[MAX];
	int year;

	printf("Enter name: ");
	scanf("%s", name);
	printf("Enter surname: ");
	scanf("%s", surname);
	printf("Enter birth year: ");
	scanf("%d", &year);

	Q = CreatePerson(name,surname,year);

	Q->Next = P->Next;
	P->Next = Q;

	return EXIT_SUCCESS;
}

int AppendList(Position P)
{
	while (P->Next != NULL)
		P = P->Next;
	
	if (NULL == P->Next)
		PrependList(P);

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