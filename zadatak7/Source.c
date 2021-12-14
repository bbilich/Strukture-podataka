#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#define MAX 128

struct _Directory;
typedef struct _Directory* Position;
typedef struct _Directory {
	char name[MAX];
	Position parent;
	Position sibling;
	Position child;
}Directory;

int MakeDirectory(Position current,char* name);
Position FindDirectory(Position current, char* name);
int PrintDirectory(Position current);
Position PreviousDirectory(Position current);
Position Command(Position current, char* name);


int main()
{
	Directory root = { "root",NULL,NULL,NULL };
	char command[MAX] = { '\0' };
	Position current = &root;

	printf("Commands: md, cd, dir, cddir, exit.\n");
	while (strcmp(command, "exit")) {
		printf("\n %s: ", current->name);
		scanf("%s", command);
		current = Command(current, command);
	}
	return 0;
}

int MakeDirectory(Position current,char* name)
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
		newDirectory->parent = current;
		newDirectory->sibling = NULL;
		newDirectory->child = NULL;
	}

	else
	{
		current = current->child;
		while (current->sibling != NULL)
			current = current->sibling;

		current->sibling = newDirectory;
		newDirectory->parent = current->parent;
		newDirectory->sibling = NULL;
		newDirectory->child = NULL;
	}


	return EXIT_SUCCESS;
}

Position FindDirectory(Position current, char* name)
{
	current = current->child;
	
	while (current != NULL && strcmp(current->name, name) )
	{
		current = current->sibling;
	}

	if (current == NULL)
	{
		printf("That directory does not exist!\n");
		return NULL;
	}

	else return current;
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

Position PreviousDirectory(Position current)
{
	if (current->parent == NULL)
		return current;
	else
		return current->parent;
}

Position Command(Position current, char* name)
{
	char temp[MAX] = { '\0' };

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
		MakeDirectory(current,temp);
		return current;
	}

	else if (strcmp(name, "cd") == 0)
		return PreviousDirectory(current);

	else if (strcmp(name, "cddir") == 0)
	{
		scanf("%s", temp);
		return FindDirectory(current, temp);
	}

	else
	{
		printf("That command is not available yet. Please,try again!\n");
		return current;
	}
}