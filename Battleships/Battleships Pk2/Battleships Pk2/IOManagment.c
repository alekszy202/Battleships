#include <stdio.h>
#include <time.h>
#include <windows.h>
#include "Defines.h"
#include "Structures.h"
#include "IOManagment.h"


/**
Odczyt danych gry z pliku tekstowego z uwzględnieniem wszystkich możliwych błędów:
-pusty plik
-nieforemna tablica
-znaki inne niż przewidziane
-występowanie innych znaków po poprawnym kodowaniu

@param adress Nazwa pliku do odczytu
@param buffer Tablica dwuwymiarowa intów z odczytu poprawnie zakodowanego pliku
@param NumberOfShips Ilość statków znaleziona w danym pliku
@return Status operacji odczytu z pliku
*/
int readFile(char* adress, int (*buffer)[COLUMNS], int* NumberOfShips)
{

	int ships = 0;
	FILE *file;

	//Sprawdza czy plik nie jest pusty
	if ((file = fopen(adress, "r")) == NULL) 
		return NOT_EXIST;
	
	//Wypełnia tablice intów 10x10 na podstawie odczytu oraz sprawdza czy sa w niej poprawne znaki

	for (int i = 0; i < ROWS; i++) 
	{
		for (int j = 0; j < COLUMNS; j++) 
		{
			char temp = fgetc(file);

			if (temp == '0') 
				*(*(buffer + i) + j) = WATER;

			else if (temp == '1') 
			{
				*(*(buffer + i) + j) = SHIP;
				ships++;
			}
			else 
			{	
				//Znak inny niż 0 lub 1
				fclose(file);
				return BAD_FORMAT;
			}
		}
		//Sprawdza czy koniec rzedu jest w poprawnym miejscu
		if (fgetc(file) != NEW_LINE && i != ROWS - 1) 
		{
			fclose(file);
			return BAD_FORMAT;
		}
	}
	//Sprawdza czy nastapil koniec pliku
	if (!feof(file)) 
		return BAD_FORMAT;
		
	

	//Poprawna ilość statków
	if (ships < MIN_SHIPS || ships > MAX_SHIPS) 
	{
		fclose(file);
		return NUMBER_OF_SHIPS_ERROR;
	}

	fclose(file);
	(*NumberOfShips) = ships;
	return FILE_FINE;
}


/**
Zapis danych gry, rozwiązań i generowanych tablic do podanego pliku
@param adress Nazwa pliku do zapisu
@param field Plansza gry do zapisu w pliku
*/
void writeFile(char* adress, Field field[][COLUMNS])
{
	FILE *file;
	file = fopen(adress, "w");

	//Zapis każdego pola gry do pliku
	for (int i = 0; i < ROWS; i++) 
	{
		for (int j = 0; j < COLUMNS; j++) 
			fprintf(file, "%d", field[i][j].value);

		if (i != ROWS-1) fprintf(file, "\n");
	}
	fclose(file);
	return;
}


/**
Zapis danych gry i statystyk po zakończonej rozgrywce do pliku tekstowego
@param adress Nazwa pliku do zapisu
@param field1 Plansza gracza 1 do zapisu w pliku
@param field2 Plansza gracza 2 do zapisu w pliku
@param stats1 Statystyki gracza 1 do zapisu w pliku
@param stats2 Statystyki gracza 2 do zapisu w pliku
*/
void saveResults(char* adress, Field field1[][COLUMNS], Field field2[][COLUMNS], Stats stats1, Stats stats2)
{

	FILE* file;
	file = fopen(adress, "w");

	fprintf(file, "PLANSZA WYGRANEGO\n");

	//Zapis każdego pola gry gracza 1 do pliku
	for (int i = 0; i < ROWS; i++) 
	{
		for (int j = 0; j < COLUMNS; j++) 
			fprintf(file, "%d", field1[i][j].value);

		if (i != ROWS-1) fprintf(file, "\n");
	}
	fprintf(file, "\n\nGracz: %s\nDo podbicia: %d\nWykonane strzaly: %d\nWykonane ruchy: %d\n", stats1.name, stats1.unsolved, stats1.tries, stats1.moves);
	fprintf(file, "\nPLANSZA PRZEGRANEGO\n");


	//Zapis każdego pola gry gracza 2 do pliku
	for (int i = 0; i < ROWS; i++) 
	{
		for (int j = 0; j < COLUMNS; j++)
			fprintf(file, "%d", field2[i][j].value);

		if (i != ROWS-1) fprintf(file, "\n");
	}
	fprintf(file, "\n\nGracz: %s\nDo podbicia: %d\nWykonane strzaly: %d\nWykonane ruchy: %d\n", stats2.name, stats2.unsolved, stats2.tries, stats2.moves);

	fclose(file);
	return;
}


/**
Zapis danych z listy logów do pliku tekstowego
@param adress Nazwa pliku do zapisu
@param pHead Głowa listy logów
*/
void writeLog(char* adress, Log *pHead)
{
	FILE* file;
	struct tm* timeinfo;
	int min, h;
	file = fopen(adress, "w");

	while (pHead)
	{
		timeinfo = pHead->timeinfo;
		if (timeinfo->tm_hour < 10)
			fprintf(file, "[0%d:", timeinfo->tm_hour);
		else
			fprintf(file, "[%d:", timeinfo->tm_hour);

		if (timeinfo->tm_min < 10)
			fprintf(file, "0%d] " ,timeinfo->tm_min);
		else
			fprintf(file, "%d] ", timeinfo->tm_min);


		if (pHead->success == 0)
			fprintf(file, "X:%d Y:%d PUDLO\n", pHead->x, pHead->y);
		else
			fprintf(file, "X:%d Y:%d ZATOPIONY!\n", pHead->x, pHead->y);

		pHead = pHead->pNext;
	}

	fclose(file);
}