#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX (50)

struct _Person;
typedef struct _Person* Position;
struct _Person
{
	char FirstName[MAX];
	char LastName[MAX];
	int BirthYear;
	Position Next;
}Person;

int PrependList(Position head);
int PrintList(Position first);
int AppendList(Position head);
Position CreatePerson(char* FirstName, char* LastName, int BirthYear);
Position FindByLastName(Position first, char* LastName);
int Erase(Position head,char* LastName);
Position FindPrevious(char* LastName, Position head);

int main()
{
	struct _Person Head;
	Head.Next = NULL;

	PrependList(&Head);
	PrependList(&Head);
	AppendList(&Head);
	AppendList(&Head);
	PrintList(Head.Next);

	Erase(&Head, "Bilic");
	PrintList(Head.Next);

}

Position CreatePerson(char* FirstName, char* LastName, int BirthYear)
{
	Position newPerson = NULL;
	newPerson = (Position)malloc(sizeof(Person));

	if (NULL == newPerson)
	{
		perror("Cannot allocate memory!\n");
		return NULL;
	}

	newPerson->BirthYear = BirthYear;
	strcpy(newPerson->FirstName, FirstName);
	strcpy(newPerson->LastName, LastName);
	newPerson->Next = NULL;

	return newPerson;
}

int PrependList(Position head)
{
	Position newPerson = NULL;
	char name[MAX], surname[MAX];
	int year;

	printf("Enter first name: ");
	scanf("%s", name);
	printf("Enter last name: ");
	scanf("%s", surname);
	printf("Enter year of birth : ");
	scanf("%d", &year);

	newPerson = CreatePerson(name, surname, year);
	if (!newPerson)
		return -1;

	newPerson->Next = head->Next;
	head->Next = newPerson;

	return EXIT_SUCCESS;
}

int PrintList(Position first)
{
	if (NULL == first)
	{
		printf("List is empty!\n");
		return -1;
	}

	else
	{
		printf("First name\tLast name\tBirth year\n");
		while (first != NULL)
		{
			printf("%s\t\t%s\t\t%d\n", first->FirstName, first->LastName, first->BirthYear);
			first = first->Next;
		}

		return EXIT_SUCCESS;
	}
}

int AppendList(Position head)
{
	while (head->Next != NULL)
		head = head->Next;
	
	if(NULL==head->Next)
		PrependList(head);

	return EXIT_SUCCESS;
}

Position FindByLastName(Position first, char* LastName)
{
	while (first != NULL && strcmp(first->LastName, LastName))
		first = first->Next;

	return first;
}

Position FindPrevious(char* LastName, Position head)
{
	Position previous;
	previous = head;
	head = head->Next;

	while (head != NULL && strcmp(head->LastName, LastName) != 0)
	{
		previous = head;
		head = head->Next;
	}

	if (NULL == head)
	{
		printf("Cannot find that element of a list!\n");
		return NULL;
	   
	}
	
	else
		return previous;
}

int Erase(Position head, char* LastName)
{
	Position temp;
	Position previous = NULL;
	previous = FindPrevious(LastName, head);

	if (NULL == previous)
	{
		printf("Could not find previous element!\n");
		return -1;
	}

	else
	{
		temp = previous->Next;
		previous->Next = temp->Next;
		free(previous);
	}

	return EXIT_SUCCESS;
}