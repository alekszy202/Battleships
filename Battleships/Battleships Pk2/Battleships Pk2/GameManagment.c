#include <stdio.h>
#include <Windows.h>
#include "Defines.h"
#include "Structures.h"
#include "GameManagment.h"
#include "IOManagment.h"
#include "ListManagment.h"


/**
Utworzenie dwuwymiarowej tablicy struktur odpowiadajacych za pojedyncze elementy planszy
@param buffer Tablica dwuwymiarowa intów przechowująca informacje z odczytu z pliku'
@param field Tablica dwuwymiarowa struktur do których zostaną zapisane informacje
@param mode Tryb tworzenia pola (to read/to play/random generated)
@param ships Ilość statków do wylosowania w trybie random
*/
void createField(int (*buffer)[COLUMNS], Field (*field)[COLUMNS], int mode, int ships) {


	//Wypełnianie elemetów tablicy strukturami z danymi pobranymi z tablicy intów
	Field tmp;
	for (int i = 0; i < ROWS; i++) 
	{
		for (int j = 0; j < COLUMNS; j++) 
		{
			//Wprowadznie wartości z tablicy intów odczytanej z pliku wejściowego
			tmp.row = i;
			tmp.column = j;
			tmp.selected = FALSE;

			if (mode == 0) 
			{
				tmp.value = *(*(buffer + i) + j);
				tmp.released = TRUE;
			}
			else if ((mode == 1) || (mode == 2))
			{
				tmp.value = WATER;
				tmp.released = FALSE;
			}

			*(*(field + i) + j) = tmp;
		}
	}

	if (mode == 1)
		(*field)->selected = TRUE;
	else if (mode == 2)
	{
		int randomI = 0;
		int randomJ = 0;

		//Pętla zapełnia losowe pola statkami aż wyczepie wszystkie zasoby do zapełnienia
		while (ships != 0) {
			randomI = (rand() % ROWS);
			randomJ = (rand() % COLUMNS);

			if (field[randomI][randomJ].value == 0) {
				field[randomI][randomJ].value = 1;
				ships--;
			}
		}
	}
	else if ((mode < 0) || (mode > 2))
		printf("Ponado bledna wartosc parametru trybu (mode:%d)\n", mode);
}



/**
Zarządzanie wyświetlaniem pojedyńczego pola do gry
@param PlayField Pole przeciwnika do narysowania w konsoli
@param ShowField Pole gramcza do narysowania w konsoli
@param exit Wybór rysowania podczas (0) lub podczas wyświetlania statystyk końcowych (1)
*/
void drawField(Field PlayField[][COLUMNS], Field ShowField[][COLUMNS], int exit)
{
	int i, j;
	//Wyświetla poniższą wiadomość nad planszami gdy trwa gra
	if (exit == 0) printf("       ---PLANSZA PRZECIWNIKA---                       ---TWOJA PLANSZA---\n");


	//Wyświetlanie górnej granicy lewej planszy
	printf("%c%c%c%c%c", CORNER_UL, HORIZONTAL_DOUBLE, HORIZONTAL_DOUBLE, HORIZONTAL_DOUBLE, HORIZONTAL_DOUBLE); //First part
	for (i = 0; i < ROWS - 2; i++)
		printf("%c%c%c%c", HORIZONTAL_DOUBLE, HORIZONTAL_DOUBLE, HORIZONTAL_DOUBLE, HORIZONTAL_DOUBLE);
	printf("%c%c%c%c   ", HORIZONTAL_DOUBLE, HORIZONTAL_DOUBLE, HORIZONTAL_DOUBLE, CORNER_UR); //Last part


	//Wyświetlanie górnej granicy prawej planszy
	printf("%c%c%c%c%c", CORNER_UL, HORIZONTAL_DOUBLE, HORIZONTAL_DOUBLE, HORIZONTAL_DOUBLE, HORIZONTAL_DOUBLE); //First part
	for (i = 0; i < ROWS - 2; i++)
		printf("%c%c%c%c", HORIZONTAL_DOUBLE, HORIZONTAL_DOUBLE, HORIZONTAL_DOUBLE, HORIZONTAL_DOUBLE);
	printf("%c%c%c%c\n", HORIZONTAL_DOUBLE, HORIZONTAL_DOUBLE, HORIZONTAL_DOUBLE, CORNER_UR); //Last part


	//Wyświtlanie wnętrza obu plansz (gracza i przeciwnika) iterując po każdym polu
	for (i = 0; i < ROWS; i++) 
	{
		printf("%c", VERTICAL_DOUBLE);
		for (j = 0; j < COLUMNS * 2; j++) 
		{
			if (j < COLUMNS && exit == GAMERUNS) 
			{
				//Zaznaczona cyfra/zero
				if (PlayField[i][j].selected == TRUE) 
				{
					SetConsoleTextAttribute(HANDLE_CONSOLE, BLACK_ON_WHITE);
					if (PlayField[i][j].released == TRUE) 
					{
						if (PlayField[i][j].value == WATER) printf(" X ");
						else printf(" %c ", SQUARE);
					}
					else printf(" ~ ");
					SetConsoleTextAttribute(HANDLE_CONSOLE, WHITE_ON_BLACK);
				}
				//Zaakceptowana cyfra
				else if (PlayField[i][j].released == TRUE) 
				{
					if (PlayField[i][j].value == WATER) 
					{
						SetConsoleTextAttribute(HANDLE_CONSOLE, RED_ON_BLACK);
						printf(" X ");
						SetConsoleTextAttribute(HANDLE_CONSOLE, WHITE_ON_BLACK);
					}
					else 
					{
						SetConsoleTextAttribute(HANDLE_CONSOLE, GREEN_ON_BLACK);
						printf(" %c ", SQUARE);
						SetConsoleTextAttribute(HANDLE_CONSOLE, WHITE_ON_BLACK);
					}

				}
				//Pusta kratka
				else printf(" ~ ");

				if (j != ROWS - 1)printf("%c", HORIZANTAL_SINGLE);
				else printf("%c   %c", VERTICAL_DOUBLE, VERTICAL_DOUBLE);
			}
			else if (j < COLUMNS) 
			{
				if (PlayField[i][j].value == SHIP) 
				{
					SetConsoleTextAttribute(HANDLE_CONSOLE, GREEN_ON_BLACK);
					printf(" %c ", SQUARE);
					SetConsoleTextAttribute(HANDLE_CONSOLE, WHITE_ON_BLACK);
				}
				//Pusta kratka
				else printf(" ~ ");

				if (j != ROWS - 1)printf("%c", HORIZANTAL_SINGLE);
				else printf("%c   %c", VERTICAL_DOUBLE, VERTICAL_DOUBLE);
			}
			else 
			{
				if (ShowField[i][j - COLUMNS].value == SHIP) 
				{
					SetConsoleTextAttribute(HANDLE_CONSOLE, GREEN_ON_BLACK);
					printf(" %c ", SQUARE);
					SetConsoleTextAttribute(HANDLE_CONSOLE, WHITE_ON_BLACK);
				}
				//Pusta kratka
				else printf(" ~ ");

				if (j - COLUMNS != ROWS - 1)printf("%c", HORIZANTAL_SINGLE);
				else printf("%c", VERTICAL_DOUBLE);
			}
		}

		if (i != ROWS - 1) 
		{
			printf("\n%c", VERTICAL_DOUBLE);

			for (j = 0; j < COLUMNS - 1; j++) 
				printf("%c%c%c%c", VERTICAL_SINGLE, VERTICAL_SINGLE, VERTICAL_SINGLE, CROSS);

			printf("%c%c%c%c", VERTICAL_SINGLE, VERTICAL_SINGLE, VERTICAL_SINGLE, VERTICAL_DOUBLE);

			printf("   %c", VERTICAL_DOUBLE);

			for (j = 0; j < COLUMNS - 1; j++)
				printf("%c%c%c%c", VERTICAL_SINGLE, VERTICAL_SINGLE, VERTICAL_SINGLE, CROSS);

			printf("%c%c%c%c\n", VERTICAL_SINGLE, VERTICAL_SINGLE, VERTICAL_SINGLE, VERTICAL_DOUBLE);
		}
	}


	//Wyświetlanie dolnej granicy planszy lewej
	printf("\n%c%c%c%c%c", CORNER_BL, HORIZONTAL_DOUBLE, HORIZONTAL_DOUBLE, HORIZONTAL_DOUBLE, HORIZONTAL_DOUBLE); //First part
	for (i = 0; i < ROWS - 2; i++) 
		printf("%c%c%c%c", HORIZONTAL_DOUBLE, HORIZONTAL_DOUBLE, HORIZONTAL_DOUBLE, HORIZONTAL_DOUBLE);
	printf("%c%c%c%c   ", HORIZONTAL_DOUBLE, HORIZONTAL_DOUBLE, HORIZONTAL_DOUBLE, CORNER_BR); //Last part


	//Wyświetlanie dolnej granicy planszy prawej
	printf("%c%c%c%c%c", CORNER_BL, HORIZONTAL_DOUBLE, HORIZONTAL_DOUBLE, HORIZONTAL_DOUBLE, HORIZONTAL_DOUBLE); //First part
	for (i = 0; i < ROWS - 2; i++) 
		printf("%c%c%c%c", HORIZONTAL_DOUBLE, HORIZONTAL_DOUBLE, HORIZONTAL_DOUBLE, HORIZONTAL_DOUBLE);
	printf("%c%c%c%c\n", HORIZONTAL_DOUBLE, HORIZONTAL_DOUBLE, HORIZONTAL_DOUBLE, CORNER_BR); //Last part

}


/**
Wyświetlanie pól do gry oraz statystyk na konsolę
@param PlayField Pole przeciwnika
@param ShowField Pole gracza
@param stats Statystyki gracza
*/
void drawGame(Field PlayField[][COLUMNS], Field ShowField[][COLUMNS], Stats stats)
{
	drawField(PlayField, ShowField, 0);
	printf("Gracz: %s\nDo podbicia: %d\nWykonane strzaly: %d\nWykonane ruchy: %d\n", stats.name, stats.unsolved, stats.tries, stats.moves);
}


/**
Poprawne zakończenie rozgrywki uwzględniając zwolnienie dynamicznie zaalokowanych pamięci oraz wyświetlenie komunikatów końcowych
@param PlayField Pole przeciwnika gracza 1
@param ShowField Pole gracza 1
@param stats Statystyki gracza 1
@param PlayField2 Pole przeciwnika gracza 2
@param ShowField2 Pole gracza 2
@param stats2 Statystyki gracza 2
@param buffer1 Zapis tablicy gracza 1 w tablicy intów
@param buffer2 Zapis tablicy gracza 2 w tablicy intów
*/
void gameEnding(Field PlayField[][COLUMNS], Field ShowField[][COLUMNS], Stats stats, Field PlayField2[][COLUMNS], Field ShowField2[][COLUMNS], Stats stats2) 
{
	system("cls");

	if (stats.unsolved == 0) 
	{
		printf("Gratulacje %s :D\nUdalo Ci sie wygrac!\n\n", stats.name);
		saveResults("result.txt", ShowField, ShowField2, stats, stats2);
	}
	else 
	{
		printf("Gratulacje %s :D\nUdalo Ci sie wygrac!\n\n", stats2.name);
		saveResults("result.txt", ShowField2, ShowField, stats2, stats);
	}

	Sleep(2000);

	//Wyœwietlenie plansz oraz statystyk1
	printf("Oto wasze plansze w kolejnosci %s, %s:\n", stats.name, stats2.name);
	drawField(ShowField, ShowField2, 1);
	Sleep(2000);

	//Zapisanie plików logów
	writeLog(strcat(stats.name,".txt"), stats.pHead);
	writeLog(strcat(stats2.name, ".txt"), stats2.pHead);

	//Zwolnienie pamięci dynamicznie zaalokowanych struktur
	deleteLog(&(stats.pHead));
	deleteLog(&(stats2.pHead));

	printf("\nDziekuje za rozgrywke! ;D\nAutor: Aleksandra Szymczak\nAEI inf Sem II\n\n");
	Sleep(2000);
}



/**
Obsługa wciskanych klawiszy podczas trwającej gry
@param PlayField Pole przeciwnika
@param ShowField Pole gracza
@param PlayField2 Pole gracza z widoku przeciwnika
@param ShowField2 Pole przeciwnika z widoku przeciwnika
@param stats Statystyki gracza
@param stats2 Statystyki przeciwnika
@param end Zmienna definiująca koniec rozgrywki
*/
void pressButton(Field PlayField[ROWS][COLUMNS], Field ShowField[ROWS][COLUMNS], Field PlayField2[ROWS][COLUMNS], Field ShowField2[ROWS][COLUMNS], Stats* stats, Stats* stats2, int* end)
{
	int key = getch(); //Odbieranie wciœniêtego klawisza
	system("cls");	//Czyszczenie konsoli

	switch (key) 
	{

	//Wcisniecie esc
	case ESC:
		printf("Czy na pewno chcesz zakonczyc gre? (Wcisnij ponownie by zaakceptowac)\n");
		key = getch();

		if (key == ESC) 
		{
			system("cls");
			(*end) = GAMEOVER;
			stats2->unsolved = 0;
		}

		system("cls");
		if ((*end) == GAMERUNS) drawGame(PlayField, ShowField, *stats);
		break;


	//Wcisniecie enter
	case ENTER:

		if (PlayField[stats->x][stats->y].released == FALSE) 
		{
			(stats->tries)++;
			PlayField[stats->x][stats->y].value = ShowField2[stats->x][stats->y].value;
			PlayField[stats->x][stats->y].released = TRUE;
			PlayField[stats->x][stats->y].selected = FALSE;

			if (ShowField2[stats->x][stats->y].value == WATER)
			{
				printf("PUDLO! Wcisnij enter by kontynuowac!\n\n");
				addLog(&(stats->pHead), stats->x, stats->y, 0);
			}
			else 
			{
				printf("TRAFIONY! Wcisnij enter by kontynuowac!\n\n"); 
				addLog(&(stats->pHead), stats->x, stats->y, 1);
				stats->unsolved--;
			}
			drawGame(PlayField, ShowField, *stats);

			if (stats->unsolved == 0) 
			{
				(*end) = 1;
				break;
			}

			//Ekran oczekiwania 3 sekund podczas zmiany gracza przed komputerem
			do 
			{
				key = getch();
				if (key == ENTER) 
				{
					system("cls");
					printf("GRACZ ZOSTANIE ZMIENIONY ZA 3 SEKUNDY!\n\n");
					drawGame(PlayField, ShowField, *stats);
					Sleep(3000);
					system("cls");
					PlayField[stats->x][stats->y].selected = TRUE;
				}
			} 
			while (key != ENTER);

			if ((*end) == GAMERUNS) drawGame(PlayField2, ShowField2, *stats2);
		}
		break;

	case ARROW:
		key = getch();
		switch (key)
		{
			//Wciśnięte strzałki
		case UP:
			if ((stats->x) != 0)
			{
				(stats->moves)++;
				(stats->x)--;
				PlayField[stats->x][stats->y].selected = TRUE;
				PlayField[(stats->x) + 1][stats->y].selected = FALSE;
			}
			break;

		case LEFT:
			if ((stats->y) != 0)
			{
				(stats->moves)++;
				(stats->y)--;
				PlayField[stats->x][stats->y].selected = TRUE;
				PlayField[stats->x][(stats->y) + 1].selected = FALSE;
			}
			break;

		case RIGHT:
			if ((stats->y) != 9)
			{
				(stats->moves)++;
				(stats->y)++;
				PlayField[stats->x][stats->y].selected = TRUE;
				PlayField[stats->x][(stats->y) - 1].selected = FALSE;
			}
			break;

		case DOWN:
			if ((stats->x) != 9)
			{
				(stats->moves)++;
				(stats->x)++;
				PlayField[stats->x][stats->y].selected = TRUE;
				PlayField[(stats->x) - 1][stats->y].selected = FALSE;
			}
			break;
		}
		drawGame(PlayField, ShowField, *stats);
		break;

	default:
		drawGame(PlayField, ShowField, *stats);
		break;
	}
	return;
}