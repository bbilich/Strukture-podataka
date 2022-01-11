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

Position Create(int X);
Position Insert(Position P, int X);
int PrintInorder(Position P, LPosition L);
int Replace(Position P);
int Random(Position P);
int WriteInFile(LPosition P, char* fname);
LPosition FindLast(LPosition P);
int Add(LPosition, int X);

int main()
{
	Position root = NULL;
	Position root2 = NULL;

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
	WriteInFile(Head.Next, "file.txt");

	Replace(root);
	PrintInorder(root,&Head);
	WriteInFile(Head.Next, "file.txt");

	root2 = Random(root2);
	PrintInorder(root2,&Head);
	WriteInFile(Head.Next, "file.txt");

	
	return EXIT_SUCCESS;
}

Position Create(int X)
{

	Position newElement = NULL;

	newElement = (Position)malloc(sizeof(Node));
	if (NULL == newElement)
	{
		printf("Cannot allocate memory!\n");
		return NULL;
	}

	newElement->element = X;
	newElement->left = NULL;
	newElement->right = NULL;

	return newElement;
}

Position Insert(Position P, int X)
{
	if (P == NULL)
		P = Create(X);

	else if (X <= P->left)
		P->left = Insert(P->left, X);

	else
		P->right = Insert(P->right, X);

	return P;
}

int PrintInorder(Position P,LPosition L)
{
	if (NULL == P)
		return EXIT_SUCCESS;


	PrintInorder(P->left, L);
	Add(L, P->element);
	printf("%d ", P->element);
	PrintInorder(P->right, L);

	return EXIT_SUCCESS;
}

int Replace(Position P)
{
	int temp = 0;
	
	if (P == NULL)
		return 0;

	else
	{
		temp = P->element;
		P->element = Replace(P->left) + Replace(P->right);
	}

	return temp + P->element;
}

int Random(Position P)
{
	int num = 0, i = 0;

	srand(time(NULL));
	for (i = 0; i < 10; i++)
	{
		num= (rand() % (90 - 10 + 1)) + 10;
		P = Insert(P, num);
	}

	return P;
}

LPosition FindLast(LPosition P)
{
	while (P->Next != NULL)
		P = P->Next;

	return P;
}

int Add(LPosition P, int X)
{
	LPosition last = NULL, new = NULL;

	last = FindLast(P);
	if (last == NULL)
	{
		printf("List is empty!");
		return -1;
	}

	new = (LPosition)malloc(sizeof(List));
	if (new == NULL)
	{
		printf("Cannot allocate memory!");
		return -1;
	}

	new->element = X;
	new->Next = P->Next;
	P->Next = new;

	return EXIT_SUCCESS;
}

int WriteInFile(LPosition P, char* fname)
{
	FILE* file = NULL;
	
	file = fopen(fname, "w");
	if (NULL == file)
	{
		printf("Cannot open the file!\n");
		return -1;
	}

	while (P != NULL)
	{
		fprintf(file, "%d ", P->element);
		P = P->Next;
	}

	fclose(file);
	return EXIT_SUCCESS;
}
