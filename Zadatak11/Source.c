#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define SIZE (100)
#define TABLE_SIZE (11)

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

int Key(char* name);
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
	Country HashTable[TABLE_SIZE];
	char string[SIZE] = { 0 };
	FILE* file = NULL;
	char country[SIZE] = { "0" }, file_name[SIZE] = { "0" }, city[SIZE] = { "0" };
	int key = 0, num = 0, i = 0;

	for (i = 0; i < TABLE_SIZE; i++)
	{
		HashTable[i].Next = NULL;
		HashTable[i].Root = NULL;
		strcpy(HashTable[i].name, " ");
	}

	file = fopen("countries.txt", "r");
	if (file == NULL)
	{
		printf("Cannot open the file! Try again.\n");
		return -1;
	}

	while (!feof(file))
	{

		fscanf(file, "%s %s", country, file_name);
		key = Key(country);
		AddCountry(&HashTable[key], country, file_name);
	}

	fclose(file);

	for (i = 0; i < TABLE_SIZE; i++)
	{
		printf("\nHash[%d]\n", i);
		Print(&HashTable[i]);
	}

	while (1)
	{
		printf("Enter the name of country that you want to search //if you want to exit type EXIT\n");
		scanf("%s", string);
		key = Key(string);

		if (strcmp(string, "EXIT") == 0)
			break;

		printf("Enter minimal population of %s cities\n", string);
		scanf("%d", &num);
		SearchCountries(&HashTable[key], string, num);
	}

	return EXIT_SUCCESS;
}

int Key(char* name)
{
	int sum = 0, i;

	for (i = 0; i < 5; i++)
		sum += name[i];

	return sum % TABLE_SIZE;
}


int ReadFromFile2(coPosition P, char* name, char* fname)
{
	FILE* file = NULL;
	char city[SIZE] = { 0 };
	int num = 0;

	file = fopen(fname, "r");
	if (file == NULL)
	{
		printf("Cannot open the file!\n");
		return -1;
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
	printf("\n\tCity: %s ", P->name);
	printf("\n\tPopulation: %d", P->population);
	PrintCity(P->Right);

	return EXIT_SUCCESS;
}

int Print(coPosition P)
{
	if (P == NULL)
		return EXIT_SUCCESS;

	else
	{
		while (P != NULL)
		{
			printf("%s\n", P->name);
			PrintCity(P->Root);
			printf("\n\n");
			P = P->Next;
		}
	}
	return EXIT_SUCCESS;
}

int SearchCountries(coPosition P, char* name, int num)
{
	if (P == NULL)
		return EXIT_SUCCESS;

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