#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define MAX 1024

struct _Polynomial;
typedef struct _Polynomial* Poly;
typedef struct _Polynomial
{
	int coefficient;
	int exponent;
	Poly Next;
}Polynomial;

int ReadFromFile(char* fileName, Poly P);
int AddElement(Poly P, int coeff, int expo);
int Print(Poly P);
int Addition(Poly P1, Poly P2, Poly S);
int Multiplication(Poly P1, Poly P2, Poly P);

int main()
{
	Polynomial Head1 = { 0,0,NULL };
	Polynomial Head2 = { 0,0,NULL };
	Polynomial Head3 = { 0,0,NULL };
	Polynomial Head4 = { 0,0,NULL };

	ReadFromFile("polynomial1.txt", &Head1);
	ReadFromFile("polynomial2.txt", &Head2);

	printf("polynomials:\n");
	Print(Head1.Next);
	Print(Head2.Next);

	Addition(&Head1, &Head2, &Head3);
	printf("Sum of polynomials\n");
	Print(Head3.Next);

	Multiplication(&Head1, &Head2, &Head4);
	printf("Multiplied polynomials\n");
	Print(Head4.Next);

	return EXIT_SUCCESS;
}

int ReadFromFile(char* fileName, Poly P)
{
	FILE* file = NULL;
	char buffer[MAX];
	int shift = 0, step = 0;
	int coeff, expo;

	file = fopen(fileName, "r");
	if (NULL == file)
	{
		perror("Cannot open the file!\n");
		return -1;
	}

	fgets(buffer, MAX, file);
	while (shift < strlen(buffer))
	{
		sscanf(buffer + shift, "%d %d %n", &coeff, &expo, &step);
		AddElement(P, coeff, expo);
		shift += step;
	}

	fclose(file);
	return EXIT_SUCCESS;
}

int AddElement(Poly P, int coeff, int expo)
{
	Poly Q = NULL;
	Poly Previous = P;

	if (NULL == Previous)
	{
		printf("That element of list does not exist!\n");
		return -1;
	}

	P = P->Next;

	while (P != NULL && P->exponent > expo)
	{
		Previous = P;
		P = P->Next;
	}

	if (P != NULL && P->exponent == expo)
	{
		P->coefficient += coeff;
	}

	else
	{
		Q = (Poly)malloc(sizeof(Polynomial));

		if (NULL == Q)
		{
			perror("Cannot allocate memory!\n");
			return -1;
		}

		Q->exponent = expo;
		Q->coefficient = coeff;
		Q->Next = P;
		Previous->Next = Q;
	}

	return EXIT_SUCCESS;
}

int Print(Poly P)
{
	if (NULL == P)
	{
		printf("List is empty!\n");
		return -1;
	}

	else
	{
		while (P != NULL)
		{
			printf("(%dX^%d) + ", P->coefficient, P->exponent);
			P = P->Next;
		}

		printf("\n\n");
		return EXIT_SUCCESS;
	}

}

int Addition(Poly P1, Poly P2, Poly S)
{
	Poly temp;

	while (P1 != NULL && P2 != NULL)
	{
		if (P1->exponent == P2->exponent) {
			AddElement(S, P1->coefficient + P2->coefficient, P1->exponent);
			P1 = P1->Next;
			P2 = P2->Next;
		}

		else if (P1->exponent > P2->exponent)
		{
			AddElement(S, P2->coefficient, P2->exponent);
			P2 = P2->Next;
		}

		else
		{
			AddElement(S, P2->coefficient, P2->exponent);
			P2 = P2->Next;
		}
	}

	if (P1 != NULL)
		temp = P1;

	else
		temp = P2;

	while (temp != NULL)
	{
		AddElement(S, temp->coefficient, temp->exponent);
		temp = temp->Next;
	}

	return EXIT_SUCCESS;
}

int Multiplication(Poly P1, Poly P2, Poly P)
{
	Poly temp = P2;
	if (NULL == temp)
	{
		printf("That element of list does not exist!\n");
		return -1;
	}

	while (P1 != NULL)
	{
		P2 = temp;
		while (P2 != NULL)
		{
			AddElement(P, P1->coefficient * P2->coefficient, P1->exponent + P2->exponent);
			P2 = P2->Next;
		}
		P1 = P1->Next;
	}

	return EXIT_SUCCESS;
}