#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include<string.h>

struct _Node;
typedef struct _Node* Position;
typedef struct _Node {
	int element;
	Position right;
	Position left;
}Node;

Position Create(int X);
Position Add(int X, Position P);
Position FindMin(Position P);
Position Delete(int X, Position P);
Position Find(int X, Position P);
Position PrintInorder(Position P);
Position PrintPostorder(Position P);
Position PrintPreorder(Position P);

int main()
{
	Position root = NULL;
	Position x = NULL;
	int num = 0, n;

	while (1) {

		printf("\n\n1 - Add new element \n");
		printf("2 - Print inorder\n");
		printf("3 - Print preorder\n");
		printf("4 - Print postorder\n");
		printf("5 - Search\n");
		printf("6 - Delete\n");
		printf("0 - Exit\n");

		printf("\n Insert number of the function: \n");
		scanf(" %d", &num);

		switch (num)
		{
		case 1:
			printf("\nInsert value of new element: \n");
			scanf(" %d", &n);
			root = Add(n, root);
			if (root == NULL)
				printf("\n An error occurred!\n");
			break;

		case 2:
			if (root == NULL)
				printf("The tree is empty.\n");
			else
				x = PrintInorder(root);
			break;

		case 3:
			if (root == NULL)
				printf("The tree is empty.\n");
			else
				x = PrintPreorder(root);
			break;

		case 4:
			if (root == NULL)
				printf("The tree is empty.\n");
			else
				x = PrintPostorder(root);
			break;

		case 5:
			printf("\nElement you are looking for: \n");
			scanf(" %d", &n);

			x = Find(n, root);
			if (x == NULL)
				printf("Element does not exist in this binary tree!\n");
			else
				printf("Element (%d) found!\n", x->element);
			break;

		case 6:
			printf("\nInsert the element you want to delete: \n");
			scanf(" %d", &n);

			root = Delete(n, root);
			if (root == NULL) printf("\nAn error occurred!.\n");
			break;

		case 0:
			printf("\n Exit. \n");
			break;

		default:
			printf("\nIncorrect function call!\n");
		}

	}

	return 0;
}

Position Create(int X)
{
	Position newEl = NULL;
	newEl = (Position)malloc(sizeof(Node));

	newEl->element = X;
	newEl->left = NULL;
	newEl->right = NULL;

	return newEl;
}

Position Add(int X, Position P)
{
	Position newEl = Create(X);

	if (P == NULL)
		return newEl;

	if (newEl->element < P->element)
		P->left = Add(newEl->element, P->left);

	else if (newEl->element > P->element)
		P->right = Add(newEl->element, P->right);

	else
	{
		printf("You already added that element of binary tree!\n");
		free(newEl);
	}

	return P;
}

Position Find(int X, Position P)
{
	if (P == NULL)
		return NULL;

	else if (X < P->element)
		return Find(X, P->left);

	else if (X > P->element)
		return Find(X, P->right);

	else
		return P;
}

Position FindMin(Position P)
{
	if (NULL == P)
		return NULL;

	else if (NULL == P->left)
		return P;

	else
		return FindMin(P->left);
}

Position Delete(int X, Position P)
{
	Position temp;

	if (P != NULL)
	{
		if (X < P->element)
			P->left = Delete(X, P->left);

		else if (X > P->element)
			P->right = Delete(X, P->right);

		else {

			if (P->left && P->right != NULL)
			{
				temp = FindMin(P->right);
				P->element = temp->element;
				P->right = Delete(P->element, P->right);
			}

			else
			{
				temp = P;

				if (NULL == P->left)
					P = P->right;
				else
					P = P->left;
				free(temp);
			}
		}

	}

	return P;
}

Position PrintInorder(Position P)
{
	if (NULL == P)
		return P;

	PrintInorder(P->left);
	printf("%d ", P->element);
	PrintInorder(P->right);

	return P;
}

Position PrintPreorder(Position P)
{
	if (NULL == P)
		return P;
	
	printf("%d ", P->element);
	PrintPreorder(P->left);
	PrintPreorder(P->right);

	return P;
}

Position PrintPostorder(Position P)
{
	if (NULL == P)
		return P;
	PrintPostorder(P->left);
	PrintPostorder(P->right);
	printf("%d ", P->element);

	return P;
}