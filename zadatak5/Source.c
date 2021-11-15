#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 1024

struct _Stack;
typedef struct _Stack* Position;
typedef struct _Stack
{
	double Element;
	Position Next;
}Stack;

double ReadFromFile(Position stack);
double Push(Position stack, double number);
double Pop(Position stack);
double Add(Position stack);
double Divide(Position stack);
double Multiply(Position stack);
double Subtract(Position stack);

int main()
{
	Stack Head = { .Element = 0, .Next = NULL };
	double result;

	result = ReadFromFile(&Head);
	printf("Postfix result = %.2lf", result);

	return EXIT_SUCCESS;
}

double Push(Position stack,double number)
{
	Position newElement = NULL;
	newElement = (Position)malloc(sizeof(Stack));

	if (NULL == newElement)
	{
		perror("Cannot allocate memory!\n");
		return -1;
	}

	else
	{
		newElement->Element = number;
		newElement->Next = stack->Next;
		stack->Next = newElement;

		return EXIT_SUCCESS;
	}
}

double Pop(Position stack)
{
	Position temp = NULL;
	double element = 0;

	if (stack == NULL)
	{
		printf("Stack is empty! Check your postfix!\n");
		return -1;
	}

	else
	{
		temp = stack->Next;
		element = temp->Element;
		stack->Next = temp->Next;
		free(temp);
	}

	return element;
}

double ReadFromFile(Position stack)
{
	FILE* file = NULL;
	char buffer[MAX];
	double number = 0;
	int step = 0, shift = 0;
	double result = 0;
	char operation ;

	file = fopen("postfix.txt", "r");
	if (file == NULL)
	{
		printf("Could not open the file!\n");
		return -1;
	}

	fgets(buffer, MAX, file);
	while (shift < sizeof(buffer))
	{
		if (sscanf(buffer + shift, "%lf %n", &number, &step) > 0)
		{
			Push(stack, number);
		}
		
		else if(sscanf(buffer + shift, "%c %n", &operation, &step) > 0)
		{
			switch (operation)
			{
			case '+':
				Add(stack);
				break;
			case '-':
				Subtract(stack);
				break;
			case '*':
				Multiply(stack);
				break;
			case '/':
				Divide(stack);
				break;
			}
		}
		shift += step;
	}

	result = Pop(stack);
	fclose(file);
	return result;
}

double Add(Position stack)
{
	double num1 = Pop(stack);
	double num2 = Pop(stack);
	double result = num1 + num2;
	Push(stack, result);

	return EXIT_SUCCESS;
}

double Subtract(Position stack)
{
	double num1 = Pop(stack);
	double num2 = Pop(stack);
	double result = num1 - num2;
	Push(stack, result);

	return EXIT_SUCCESS;
}

double Multiply(Position stack)
{
	double num1 = Pop(stack);
	double num2 = Pop(stack);
	double result = num1 * num2;
	Push(stack, result);

	return EXIT_SUCCESS;
}

double Divide(Position stack)
{
	double num1 = Pop(stack);
	double num2 = Pop(stack);

	if (num2 == 0)
	{
		printf("Cannot divide with ZERO! Check your postfix!\n");
		return -2;
	}
	
	else
	{
		double result = num1 / num2;
		Push(stack, result);
	}

	return EXIT_SUCCESS;
}