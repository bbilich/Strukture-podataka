#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<time.h>

struct _Node;
typedef struct _Node* Position;
typedef struct _Node {
	int element;
	Position right;
	Position left;
}Node;

struct _List;
typedef struct _List* LPosition;
typedef struct _List {
	int element;
	LPosition Next;
}List;

Position Insert(Position P, int X);
Position PrintInorder(Position P, LPosition L);
int Replace(Position P);
Position Random(Position P);
int AddToList(LPosition P, int X);
int WriteInFile(LPosition P, char* name);

int main()
{
	Position root = NULL;
	int num[] = { 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 };
	int i;
	List Head = { 0,NULL };

	root = Insert(root, 2);
	root = Insert(root, 5);
	root = Insert(root, 7);
	root = Insert(root, 8);
	root = Insert(root, 11);
	root = Insert(root, 1);
	root = Insert(root, 4);
	root = Insert(root, 2);
	root = Insert(root, 3);
	root = Insert(root, 7);
	PrintInorder(root, &Head);

	printf("\n\n");
	root->element = Replace(root->left) + Replace(root->right);
	PrintInorder(root, &Head);
	WriteInFile(Head.Next, "file.txt");
	printf("\n\n");
	
	return EXIT_SUCCESS;
}

Position Insert(Position P, int X)
{
	Position newEl;

	if (P == NULL)
	{
		newEl = (Position)malloc(sizeof(Node));

		newEl->element = X;
		newEl->left = NULL;
		newEl->right = NULL;

		return newEl;
	}

	if (X >= P->element)
		P->left = Insert(P->left, X);

	if (X <= P->element)
		P->right = Insert(P->right, X);

	return P;
}

int Replace(Position P)
{
	int temp;

	if (P == NULL)
		return 0;

	temp = P->element;
	P->element = Replace(P->left) + Replace(P->right);
	return P->element + temp;
}

Position Random(Position P)
{
	int i = 0, num = 0;
	srand(time(NULL));

	for (i = 0; i < 10; i++)
	{
		num = rand() % 80 + 10;
		P = Insert(P, num);
	}
	return P;
}

int AddToList(LPosition P, int X)
{
	LPosition Q;
	while (P != NULL)
	{
		if (P->Next == NULL)
		{
			Q = (LPosition)malloc(sizeof(List));
			Q->element = X;
			Q->Next = Q;
			Q->Next = NULL;
		}

		P = P->Next;
	}

	return EXIT_SUCCESS;
}

int WriteInFile(LPosition P, char* name)
{
	FILE* file = NULL;
	file = fopen(name, "w");
	if (file == NULL)
	{
		printf("Cannot open the file!\n");
		return -1;
	}

	while (P != NULL)
	{
		fprintf(file, "%d ", P->element);
		P = P->Next;
	}
	fprintf(file, "\n");
	fclose(file);

	return EXIT_SUCCESS;
}

Position PrintInorder(Position P,LPosition L)
{
	if (P == 0)
		return P;

	PrintInorder(P->left, L);
	printf("%d ", P->element);
	AddToList(L, P->element);
	PrintInorder(P->right, L);

	return P;
}