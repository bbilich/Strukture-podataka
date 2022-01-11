#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 100

struct _City;
typedef struct _City* ciPosition;
typedef struct _City
{
	char name[SIZE];
	int population;
	ciPosition Next;
}City;


struct _Country;
typedef struct _Country* coPosition;
typedef struct _Country
{
	char name[SIZE];
	coPosition Left;
	coPosition Right;
	ciPosition Head;
}Country;

coPosition ReadFromFile(char* name, coPosition P);
int ReadFromFile2(ciPosition P, char* name, char* fname);
coPosition CreateCountry(char* name, char* file_name);
coPosition AddCountry(coPosition P, char* name, char* file_name);
ciPosition MakeHead(ciPosition P);
ciPosition CreateCity(char* name, int num);
ciPosition AddCity(ciPosition P, char* name, int num);
int PrintCity(ciPosition P);
int Print(coPosition P);
int SearchCities(ciPosition P, int num);
int SearchCountries(coPosition P, char* name,int num);

int main()
{
	coPosition Root = NULL, temp = NULL;
	char string[SIZE] = { 0 };
	int num = 0;

	Root = ReadFromFile("countries.txt", Root);
	Print(Root);
	printf("\n\n");
	
	while (1)
	{
		printf("Enter the name of country that you want to search //if you want to exit type EXIT\n");
		scanf("%s", string);

		if (strcmp(string, "EXIT") == 0)
			break;

		printf("Enter minimal population of %s cities\n", string);
		scanf("%d", &num);
		SearchCountries(Root, string, num);
	}
	return EXIT_SUCCESS;
}

coPosition ReadFromFile(char* name, coPosition P)
{
	FILE* file = NULL;
	char string[SIZE] = { 0 }, file_name[SIZE] = { 0 };

	file = fopen(name, "r");
	if (file == NULL)
	{
		printf("Cannot open the file!\n");
		return NULL;
	}

	while (!feof(file))
	{
		if (strcmp(name, "countries.txt") == 0)
		{
			fscanf(file, "%s %s", string, file_name);
			P = AddCountry(P, string, file_name);
		}
	}

	fclose(file);
	return P;
}

coPosition CreateCountry(char* name, char* file_name)
{
	coPosition newCountry = NULL;
	
	newCountry = (coPosition)malloc(sizeof(Country));
	if (newCountry == NULL)
	{
		printf("Cannot allocate memory!");
		return NULL;
	}

	newCountry->Head = MakeHead(newCountry->Head);
	strcpy(newCountry->name, name);
	newCountry->Left = NULL;
	newCountry->Right = NULL;

	ReadFromFile2(newCountry->Head, name, file_name);

	return newCountry;
}

int ReadFromFile2(ciPosition P, char* name, char* fname)
{
	FILE* file = NULL;
	char city[SIZE] = { 0 };
	int num = 0;


	file = fopen(fname, "r");
	if (file == NULL)
	{
		printf("Cannot open the file!\n");
		return NULL;
	}

	while (!feof(file))
	{
		fscanf(file, "%s %d", city, &num);
		P = AddCity(P, city, num);
	}

	fclose(file);
	return EXIT_SUCCESS;
}

ciPosition MakeHead(ciPosition P)
{
	ciPosition new;

	new = (ciPosition)malloc(sizeof(City));
	if (new == NULL)
	{
		printf("Cannot allocate memory!");
		return NULL;
	}

	strcpy(new->name, " ");
	new->Next = NULL;
	new->population = 0;

	return new;
}

coPosition AddCountry(coPosition P, char* name, char* file_name)
{

	if (P == NULL)
		P = CreateCountry(name, file_name);

	else if (strcmp(name, P->name) < 0)
		P->Left = AddCountry(P->Left, name, file_name);

	else
		P->Right = AddCountry(P->Right, name, file_name);
	
	return P;
}

ciPosition CreateCity(char* name, int num)
{
	ciPosition newCity = NULL;

	newCity = (ciPosition)malloc(sizeof(City));
	if (newCity == NULL)
	{
		printf("Cannot allocate memory!\n");
		return NULL;
	}

	strcpy(newCity->name, name);
	newCity->population = num;
	newCity->Next = NULL;

	return newCity;
}

ciPosition AddCity(ciPosition P, char* name, int num)
{
	ciPosition newCity = NULL;
	ciPosition temp = P;
	newCity = CreateCity(name, num);

	if (newCity == NULL)
	{
		printf("Memory allocation failed!");
		return NULL;
	}

	while ((temp->Next != NULL) && (strcmp(temp->Next->name, newCity->name) <= 0))
		temp = temp->Next;

	newCity->Next = temp->Next;
	temp->Next = newCity;

	return P;
}


int PrintCity(ciPosition P)
{
	if (P == NULL)
	{
		printf("List is empty!\n");
		return -1;
	}

	else
	{
		printf("City:");
		while (P != NULL)
		{
			printf(" %s", P->name);
			P = P->Next;
		}
	}

	return EXIT_SUCCESS;
}

int Print(coPosition P)
{
	if (P == NULL)
		return -1;

	Print(P->Left);
	printf("Country: %s\n", P->name);
	PrintCity(P->Head->Next);
	printf("\n");
	Print(P->Right);

	return EXIT_SUCCESS;
}

int SearchCities(ciPosition P, int num)
{
	if (P == NULL)
		return EXIT_SUCCESS;

	while (P != NULL)
	{
		if (P->population > num)
			printf(" %s ", P->name);
		P = P->Next;
	}
	printf("\n");

	return EXIT_SUCCESS;
}

int SearchCountries(coPosition P, char* name,int num)
{
	if (P == NULL)
		return EXIT_SUCCESS;

	else if (strcmp(P->name, name) == 0)
		SearchCities(P->Head, num);

	else if (strcmp(P->name, name) < 0)
		 SearchCountries(P->Left, name,num);

	else
	     SearchCountries(P->Right, name,num);

	return EXIT_SUCCESS;
}