#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 200

struct _person;
typedef struct _person* Position;

typedef struct _person
{
	char firstName[MAX];
	char lastName[MAX];
	int birthYear;
	Position next;
}person;



int InsertB(Position P)
{
	Position Q = NULL;
	char name[MAX], lastN[MAX];
	int year;

	printf("Enter first name: ");
	scanf("%s", name);
	printf("Enter last name: ");
	scanf("%s", lastN);
	printf("Enter year of birth: ");
	scanf("%d", &year);

	Q = createStud(name, lastN, year);
	Q->next = P->next;
	P->next = Q;

	return 0;
}

Position createStud(char *name, char* lastN, int year)
{
	Position P = NULL;
	P = (Position)malloc(sizeof(person));

	if (NULL == P)
	{
		printf("Memory allocation failed!\n");
		return NULL;
	}

	strcpy(P->firstName, name);
	strcpy(P->lastName, lastN);
	P->birthYear = year;
	P->next = NULL;

	return P;
}

int InsertA(Position P)
{
	while (P->next != NULL)
	{
		P = P->next;
	}

	if (NULL == P->next)
	{
		InsertB(P);
	}

	else
	{
		printf("Cannot find the last element of list!\n");
		return -1;
	}

	return 0;
}
Position Search(char *str, Position P)
{
	while (P != NULL && strcmp(P->lastName, str))
	    P = P->next;
	
	if (NULL == P)
		printf("Wanted element is not in the list!\n");
	
	
	else
		return P;
}

Position SearchP(Position P, char *string)
{
	Position prev = P;
	P = P->next;

	while (P->next != NULL && strcmp(P->lastName, string) != 0)
	{
		prev = P;
		P = P->next;
	}

	if (NULL == P->next)
	{
		printf("Wanted element is not in the list!\n");
		return NULL;
	}

	else
		return prev;
}

int Erase(char *string, Position P)
{
	Position prev = NULL;
	prev = SearchP(P, string);

	if (NULL == prev)
	{
		printf("Search of element failed!\n");
		return -1;
	}

	else
	{
		P = prev->next;
		prev->next = P->next;
		free(P);
	}
}

int Print(Position head)
{
	Position P = NULL;

	for(P=head->next; P != NULL; P=P->next)
		{
			printf("Student %s %s was born in %d\n", P->firstName, P->lastName, P->birthYear);
		}
		return 0;
}

int main()
{
	Position head = NULL;
	head = (Position)malloc(sizeof(person));
	head->next = NULL;

	char firstName[MAX], lastName[MAX];
	int year;

	InsertB(head);
	InsertB(head);
	InsertA(head);
	InsertA(head);

	Print(head);
	printf("\n\n\n");

	printf("Enter a last name of a student that you want to erase: ");
	scanf("%s", lastName);
	Erase(lastName, head);
    Print(head);

	
	return 0;
}
