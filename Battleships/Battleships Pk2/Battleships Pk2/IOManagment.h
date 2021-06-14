#ifndef IO_MANAGMENT
#define IO_MANAGMENT

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
int readFile(char* adress, int (*buffer)[COLUMNS], int* NumberOfShips);


/**
Zapis danych gry, rozwiązań i generowanych tablic do podanego pliku
@param adress Nazwa pliku do zapisu
@param field Plansza gry do zapisu w pliku
*/
void writeFile(char* adress, Field field[][COLUMNS]);


/**
Zapis danych gry i statystyk po zakończonej rozgrywce do pliku tekstowego
@param adress Nazwa pliku do zapisu
@param field1 Plansza gracza 1 do zapisu w pliku
@param field2 Plansza gracza 2 do zapisu w pliku
@param stats1 Statystyki gracza 1 do zapisu w pliku
@param stats2 Statystyki gracza 2 do zapisu w pliku
*/
void saveResults(char* adress, Field field1[][COLUMNS], Field field2[][COLUMNS], Stats stats1, Stats stats2);


/**
Zapis danych z listy logów do pliku tekstowego
@param adress Nazwa pliku do zapisu
@param pHead Głowa listy logów
*/
void writeLog(char* adress, Log* pHead);

#endif
