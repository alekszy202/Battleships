#include <stdio.h>
#include "Defines.h"
#include "Structures.h"
#include "ProgramManagment.h"
#include "GameManagment.h"
#include "IOManagment.h"
#include "ListManagment.h"


/**
Obsługa wszystkich funkcji, zmiennych i struktur zarządzających grą
@param argc Liczba przełączników podanych przy włączeniu programu
@param argv[] Przełączniki podane przy włączaniu programu
*/
void PlayMode(int argc, char* argv[]) 
{

	//Statystyki gry i graczy
	int end = GAMERUNS; //Gdy "1" - koniec gry
	Stats stats1 = (Stats) { .unsolved = 100, .x = 0, .y = 0, .tries = 0, .moves = 0, .pHead = NULL };
	Stats stats2 = (Stats) { .unsolved = 100, .x = 0, .y = 0, .tries = 0, .moves = 0, .pHead = NULL };


	//Odczyt i walidacja pliku gracza nr 1
	int buffer1[ROWS][COLUMNS];
	int FileError = readFile(argv[3], buffer1, &(stats2.unsolved));
	if (FileError == BAD_FORMAT) 
	{
		printf("Zly format pliku wejsciowego nr 1!\n");
		return;
	}
	else if (FileError == NOT_EXIST) 
	{
		printf("Brak pliku nr 1 o podanej nazwie/rozszerzeniu!\n");
		return;
	}
	else if (FileError == NUMBER_OF_SHIPS_ERROR) 
	{
		printf("Nieprawidlowa ilosc statkow w pliku nr 1! Powinno byc ich w przedziale <5,20> \n");
		return;
	}


	//Odczyt i walidacja pliku gracza nr 2
	int buffer2[ROWS][COLUMNS];
	FileError= readFile(argv[5], buffer2, &(stats1.unsolved));

	if (FileError == BAD_FORMAT) 
	{
		printf("Zly format pliku wejsciowego nr 2!\n");
		return;
	}
	else if (FileError == NOT_EXIST) 
	{
		printf("Brak pliku nr 2 o podanej nazwie/rozszerzeniu!\n");
		return;
	}
	else if (FileError == NUMBER_OF_SHIPS_ERROR)
	{
		printf("Nieprawidlowa ilosc statkow w pliku nr 2! Powinno byc ich w przedziale <5,20> \n");
		return;
	}


	Field ShowField1[ROWS][COLUMNS]; 
	createField(buffer1, ShowField1, 0, 0); //pojemnik gracza 1

	Field PlayField1[ROWS][COLUMNS];
	createField(NULL, PlayField1, 1, 0); //symulacja planszy gracza 2 dla gracza 1
	
	Field ShowField2[ROWS][COLUMNS];
	createField(buffer2, ShowField2, 0, 0); //pojemnik gracza 2

	Field PlayField2[ROWS][COLUMNS];
	createField(NULL, PlayField2, 1, 0); //symulacja planszy gracza 1 dla gracza 2


	//Odczyt nazw graczy
	printf("Proszę ograniczyć się do nazwy z 15 znakami\n");
	printf("Podaj nazwe gracza nr 1: ");
	scanf_s("%15s%*[^\n]", stats1.name, sizeof(stats1.name));
		
	printf("\nPodaj nazwe gracza nr 2: ");
	scanf_s("%15s%*[^\n]", stats2.name, sizeof(stats2.name));

	system("cls");
	drawGame(PlayField1, ShowField1, stats1);


	//Pętla powtarzająca się do czasu zakończenia gry
	while (end != GAMEOVER) 
	{
		if (stats1.tries == stats2.tries) 
			pressButton(PlayField1, ShowField1, PlayField2, ShowField2, &stats1, &stats2, &end);
		else 
			pressButton(PlayField2, ShowField2, PlayField1, ShowField1, &stats2, &stats1, &end);
	}

	//Napisy i statystyki koncowe
	gameEnding(PlayField1, ShowField1, stats1, PlayField2, ShowField2, stats2);

	return;
}



/**
Obsługa trybu generowania pustych tablic do zapełnienia przed graczy
@param argc Liczba przełączników podanych przy włączeniu programu
@param argv[] Przełączniki podane przy włączaniu programu
*/
void EmptyMode(int argc, char* argv[])
{
	Field empty[ROWS][COLUMNS];
	createField(NULL, empty, 1, 0); //Generowanie pustego pola
	writeFile("p1.txt", empty);	//Zapis pustego pola do pliku
	writeFile("p2.txt", empty);
}



/**
Tryb pseudolosujący plansze do gry o podanych przez graczy parametrach
@param argc Liczba przełączników podanych przy włączeniu programu
@param argv[] Przełączniki podane przy włączaniu programu
*/
void BuildMode(int argc, char* argv[])
{
	int ships = atoi(argv[3]); //zamiana char* na int -> casting
	
	if ((ships == 0) && (strcmp(argv[3], "0") != 0))
	{
		printf("Trzeci przeladnik nie jest liczba!\n");
		return;
	}

	//Liczba statkow musi byc z przedzialu <5,20>
	if (ships > MIN_SHIPS - 1 && ships < MAX_SHIPS + 1)
	{
		//Pseudolosowanie wartoœci pola i zapis do pliku o podanej nazwie 
		Field field[ROWS][COLUMNS];
		createField(NULL, field, 2, ships);
		writeFile(argv[2], field);
		printf("Plansza wygenerowana poprawnie!\n");
	}
	else printf("Nieprawidlowa liczba statkow w przelacznikach! Powinno byc ich w przedziale <5,20> \n");

	return;
}