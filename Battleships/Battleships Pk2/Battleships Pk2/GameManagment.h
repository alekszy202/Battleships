#ifndef GAMEMANAGMENT
#define GAMEMANAGMENT

#include <stdlib.h>
#include <Windows.h>


/**
Utworzenie dwuwymiarowej tablicy struktur odpowiadajacych za pojedyncze elementy planszy
@param buffer Tablica dwuwymiarowa intów przechowująca informacje z odczytu z pliku'
@param field Tablica dwuwymiarowa struktur do których zostaną zapisane informacje
@param mode Tryb tworzenia pola (to read/to play/random generated)
@param ships Ilość statków do wylosowania w trybie random
*/
void createField(int (*buffer)[COLUMNS], Field (*field)[COLUMNS], int mode, int ships);


/**
Zarządzanie wyświetlaniem pól do gry
@param PlayField Pole przeciwnika do narysowania w konsoli
@param ShowField Pole gramcza do narysowania w konsoli
@param exit Wybór rysowania podczas (0) lub podczas wyświetlania statystyk końcowych (1)
*/
void drawField(Field PlayField[][COLUMNS], Field ShowField[][COLUMNS], int exit);


/**
Wyœwietlanie pól do gry oraz statystyk na konsolê
@param PlayField Pole przeciwnika
@param ShowField Pole gracza
@param stats Statystyki gracza
*/
void drawGame(Field PlayField[][COLUMNS], Field ShowField[][COLUMNS], Stats stats);


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
void gameEnding(Field PlayField[][COLUMNS], Field ShowField[][COLUMNS], Stats stats, Field PlayField2[][COLUMNS], Field ShowField2[][COLUMNS], Stats stats2);


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
void pressButton(Field PlayField[ROWS][COLUMNS], Field ShowField[ROWS][COLUMNS], Field PlayField2[ROWS][COLUMNS], Field ShowField2[ROWS][COLUMNS], Stats* stats, Stats* stats2, int* end);
#endif