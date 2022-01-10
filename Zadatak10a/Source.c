#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define SIZE (100)

struct _City;
typedef struct _City* ciPosition;
typedef struct _City
{
	char name[SIZE];
	int population;
	ciPosition Left;
	ciPosition Right;
}City;

struct _Country;
typedef struct _Country* coPosition;
typedef struct _Country
{
	char name[SIZE];
	coPosition Next;
	ciPosition Root;
}Country;

int Choose(coPosition P);
int ReadFromFile(coPosition P, char* name);
int ReadFromFile2(coPosition P, char* name, char* fname);
int AddCountry(coPosition P, char* country, char* file);
coPosition CreateCountry(char* name, char* fname);
ciPosition CreateCity(char* name, int num);
ciPosition AddCity(char* name, int num, ciPosition P);
int PrintCity(ciPosition P);
int Print(coPosition P);
int SearchCities(ciPosition P, int num);
int SearchCountries(coPosition P, char* name, int num);

int main()
{
	Country Head = { {"0"},NULL,NULL };
	
	Choose(&Head);

	return EXIT_SUCCESS;
}

int Choose(coPosition P)
{
	char string[SIZE] = { 0 };
	int num = 0;

	ReadFromFile(P, "countries.txt");
	Print(P->Next);
	printf("\n\n");

	while (1)
	{
		printf("Enter the name of country that you want to search //if you want to exit type EXIT\n");
		scanf("%s", string);

		if (strcmp(string, "EXIT") == 0)
			break;

		printf("Enter minimal population of %s cities\n", string);
		scanf("%d", &num);
		SearchCountries(P->Next, string, num);
	}

	return EXIT_SUCCESS;
}

int ReadFromFile(coPosition P, char* name)
{
	FILE* file = NULL;
	file = fopen(name, "r");
	char country[SIZE] = { "0" }, file_name[SIZE] = { "0" }, city[SIZE] = { "0" };
	int num = 0;

	if (file == NULL)
	{
		printf("Cannot open the file! Try again.\n");
		return -1;
	}

	while (!feof(file))
	{
		if (strcmp(name, "countries.txt") == 0)
		{
			fscanf(file, "%s %s", country, file_name);
			AddCountry(P, country, file_name);
		}

	}

	fclose(file);
	return EXIT_SUCCESS;
}

int ReadFromFile2(coPosition P, char* name, char* fname)
{
	FILE* file = NULL;
	char city[SIZE] = { 0 };
	int num = 0;

	file = fopen(fname, "r");
	if (file == 0)
	{
		printf("Cannot open the file!\n");
		return NULL;
	}

	while (!feof(file))
	{
		fscanf(file, "%s %d", city, &num);
		P->Root = AddCity(city, num, P->Root);
	}

	fclose(file);
	return EXIT_SUCCESS;
}

coPosition CreateCountry(char* name, char* fname)
{
	coPosition newCountry = NULL;

	newCountry = (coPosition)malloc(sizeof(Country));
	if (newCountry == NULL)
	{
		printf("Error! Cannot allocate memory!\n");
		return NULL;
	}

	strcpy(newCountry->name, name);
	newCountry->Next = NULL;
	newCountry->Root = NULL;

	ReadFromFile2(newCountry, name, fname);
	
	return newCountry;
}

int AddCountry(coPosition head, char* country, char* file)
{
	coPosition newCountry = NULL;
	coPosition temp = head;
	newCountry = CreateCountry(country, file);

	if (newCountry == NULL)
	{
		printf("Memory allocation failed!\n");
		return -1;
	}

	while ((temp->Next != NULL) && (strcmp(newCountry->name, temp->Next->name) > 0))
		temp = temp->Next;


	newCountry->Next = temp->Next;
	temp->Next = newCountry;

	return EXIT_SUCCESS;
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
	newCity->Left = NULL;
	newCity->Right = NULL;

	return newCity;
}

ciPosition AddCity(char* name, int num, ciPosition P)
{
	if (P == NULL)
		P = CreateCity(name, num);

	else if (num < P->population)
		P->Left = AddCity(name, num, P->Left);

	else if (num > P->population)
		P->Right = AddCity(name, num, P->Right);

	else if (strcmp(name, P->name) > 0)
		P->Left = AddCity(name, num, P->Left);

	else if (strcmp(name, P->name) < 0)
		P->Right = AddCity(name, num, P->Right);

	return P;
}

int PrintCity(ciPosition P)
{
	if (NULL == P)
		return -1;

	PrintCity(P->Left);
	printf(" %s ", P->name);
	PrintCity(P->Right);

	return EXIT_SUCCESS;
}

int Print(coPosition P)
{
	if (P == NULL)
	{
		printf("List is empty!\n");
		return -1;
	}

	else
	{
		while (P != NULL)
		{
			printf("Country: %s\n", P->name);
			printf("City: ");
			PrintCity(P->Root);
			printf("\n");
			P = P->Next;
		}
		return EXIT_SUCCESS;
	}
}

int SearchCountries(coPosition P, char* name, int num)
{
	if (P == NULL)
	{
		printf("That country does not exit in file countries.txt. Please check your file!\n");
		return -1;
	}

	while (P != NULL)
	{
		if (strcmp(P->name, name) == 0)
		{
			printf("Country: %s\n", name);
			printf("Cities with population bigger than %d:\n", num);
			SearchCities(P->Root, num);
			printf("\n\n");
		}
		P = P->Next;
	}

	return EXIT_SUCCESS;
}

int SearchCities(ciPosition P, int num)
{
	if (P == NULL)
		return EXIT_SUCCESS;


	SearchCities(P->Left, num);

	if (P->population > num)
		printf("City %s, population = %d\n", P->name, P->population);

	SearchCities(P->Right, num);

	return EXIT_SUCCESS;
}
