#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#define MAX_SIZE 100

typedef struct _Article* APosition;
typedef struct _Article
{
	char string[50];
	int quantity;
	float price;
	APosition Next;
}Article;

typedef struct _Bill* BPosition;
typedef struct _Bill
{
	APosition articles;
	int year;
	int month;
	int day;
	BPosition Next;
}Bill;

int ReadBills(BPosition P, char* FileName);
int AddArticleSorted(APosition P, char* String, int Quantity, float Price);
BPosition AddBillSorted(BPosition P, int Year, int Month, int Day);
int PrintArticles(APosition P);

int main()
{
	Bill HeadBill = { NULL,0,0,0,NULL };
	BPosition BHeadBill = &HeadBill;

	ReadBills(BHeadBill, "racuni.txt");

	return 0;
}

int ReadBills(BPosition P, char* FileName)
{
	BPosition tempP = NULL;
	FILE* File = NULL;
	FILE* BillFile = NULL;
	char BillFileName[MAX_SIZE], tempName[MAX_SIZE];
	int tempDay = 0, tempYear = 0, tempMonth = 0, tempQuantity = 0, tempPrice = 0, counter = 0;

	File = fopen(FileName, "r");
	if (File == NULL)
	{
		printf("Error! Cannot open the file!\n");
		return -1;
	}

	while (!feof(File))
	{
		fscanf(File, "%s", &BillFileName);
		BillFile = fopen(BillFileName, "r");
		if (BillFile == NULL)
		{
			printf("Error! Cannot open the file!\n");
			return -1;
		}

		counter = 0;

		while (!feof(BillFile))
		{
			if (counter == 0)
			{
				fscanf(BillFile, "%d-%d-%d", &tempYear, &tempMonth, &tempDay);
				tempP = AddBillSorted(P, tempYear, tempMonth, tempDay);
			}

			else if (fscanf(BillFile, "%s %d %f", &tempName, &tempQuantity, &tempPrice) != EOF)
			{
				AddArticleSorted(tempP, tempName, tempQuantity, tempPrice);
			}

			else
				break;
			++counter;
		}

		fclose(BillFile);
	}

	return EXIT_SUCCESS;
}

int AddArticleSorted(APosition P, char* String, int Quantity, float Price)
{
	APosition Q;
	Q = (APosition)malloc(sizeof(Article));

	strcpy(Q->string, String);
	Q->quantity = Quantity;
	Q->price = Price;

	while ((P->Next != NULL) && strcmp(P->Next->string, String) < 0)
		P = P->Next;

	Q->Next = P->Next;
	P->Next = Q;

	return EXIT_SUCCESS;
}

BPosition AddBillSorted(BPosition P, int Year, int Month, int Day)
{
	BPosition Q;
	Article ArticleHead = { "",0,0,NULL };
	APosition PArticleHead;
	PArticleHead = &ArticleHead;

	Q = (BPosition)malloc(sizeof(Bill));

	Q->articles = PArticleHead;
	Q->year = Year;
	Q->month = Month;
	Q->day = Day;

	while (P->Next != NULL && ((P->Next->year > Year) || (P->Next->year == Year && P->Next->month > Month) || (P->Next->year == Year && P->Next->month == Month && P->Next->day >= Day)))
		P = P->Next;

	Q->Next = P->Next;
	P->Next = Q;

	return Q;
}

int PrintArticles(APosition P)
{
	P = P->Next;
	while (P != NULL)
	{
		printf("%s %f %d.\n", P->string, P->price, P->quantity);
		P = P->Next;
	}

	return EXIT_SUCCESS;
}