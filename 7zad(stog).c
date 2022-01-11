#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1024

struct _directory;
typedef struct _directory* Position;
typedef struct _directory {
	char name[MAX_LENGTH];
	Position sibling;
	Position child;
}Directory;

struct _stack;
typedef struct _stack* Pos;
typedef struct _stack {
	Position directory;
	Pos next;
}Stack;

Position Pop(Pos p);
int Push(Position current, Pos P);
int MakeDirectory(Position current, char* name);
Position Command(Position current, Pos head, char* name);
Position ChangeDirectory(Position current, Pos P, char* name);
int PrintDirectory(Position current);
Position ChangeToPrevious(Pos head);

int main()
{
	Directory root = { "C",NULL,NULL};
	Stack head = { NULL,NULL };
	char command[100] = { '\0' };
	Position current = &root;

	printf("Commands: md, cd, dir, cd.., exit.\n");
	while (strcmp(command, "exit")) {
		printf("\n %s: ", current->name);
		scanf("%s", command);
		current = Command(current, &head, command);
	}

	return EXIT_SUCCESS;
}

Position Pop(Pos P)
{
	Pos temp=NULL;
	Position element = NULL;

	while (P->next->next != NULL)
		P = P->next;

	element = P->next->directory;
	temp = P->next;
	P->next = temp->next;
	free(temp);

	return element;
}

int Push(Position temp, Pos P)
{
	Pos new = NULL;

	new = (Pos)malloc(sizeof(Stack));

	if (new == NULL) 
	{
		printf("Cannot allocate memory!\n");
		return -1;
	};

	new->directory = NULL;
	new->next = NULL;


	if (P->next == NULL)
	{
		new->directory = temp;
		P->next = new;
	}
	else
	{
		while (P->next != NULL)
			P = P->next;

		new->directory = temp;
		P->next = new;
	}
	return EXIT_SUCCESS;
}

int MakeDirectory(Position current, char* name)
{
	Position newDirectory = NULL;

	newDirectory = (Position)malloc(sizeof(Directory));
	if (newDirectory == NULL)
	{
		perror("Cannot allocate memory!\n");
		return -1;
	}

	strcpy(newDirectory->name, name);

	if (current->child == NULL)
	{
		current->child = newDirectory;
		newDirectory->sibling = NULL;
		newDirectory->child = NULL;
	}

	else
	{
		current = current->child;
		while (current->sibling != NULL)
			current = current->sibling;

		current->sibling = newDirectory;
		newDirectory->sibling = NULL;
		newDirectory->child = NULL;
	}

	return EXIT_SUCCESS;
}

Position ChangeDirectory(Position current,Pos P, char* name)
{
	Position temp = current;
	Push(current, P);

	current = current->child;

	while (current != NULL && strcmp(current->name, name) !=0)
		current = current->sibling;

	if (current == NULL)
	{
		printf("That directory does not exist!\n");
		return temp;
	}

	else 
		return current;
}

Position ChangeToPrevious(Pos head)
{
	return Pop(head);
}


int PrintDirectory(Position current)
{
	current = current->child;

	if (current == NULL)
		printf("Directory is empty!\n");

	while (current != NULL)
	{
		printf("<DIR> %s\n", current->name);
		current = current->sibling;
	}

	return EXIT_SUCCESS;
}

Position Command(Position current, Pos head, char* name)
{
	char temp[100] = { '\0' };

	if (strcmp(name, "dir") == 0)
	{
		PrintDirectory(current);
		return current;
	}

	else if (strcmp(name, "exit") == 0)
		return current;

	else if (strcmp(name, "md") == 0)
	{
		scanf("%s", temp);
		MakeDirectory(current, temp);
		return current;
	}

	else if (strcmp(name, "cd..") == 0)
	{
			return ChangeToPrevious(head);
	}
		

	else if (strcmp(name, "cd") == 0)
	{
		scanf("%s", temp);
		return ChangeDirectory(current, head, temp);
	}

	else
	{
		printf("That command is not available yet. Please,try again!\n");
		return current;
	}
}