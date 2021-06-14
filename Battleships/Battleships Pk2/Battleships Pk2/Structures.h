#ifndef STRUCTURES
#define STRUCTURES


/**
Struktura pojedynczego pola
@param value Wartość pola- czy na polu jest statek (0/1)
@param row Rząd danego pola
@param column Kolumna danego pola
@param selected Czy dane pole jest aktualnie zaznaczone przez gracza
@param released W przypadku pola przeciwnika czy dane pole zostało odkryte
*/
typedef struct Field {
	int value;
	int row, column;
	int selected;
	int released;
} Field;


/**
Struktura przechowuje dane na temat każdego wykonanego przez gracza strzału
@param x Współrzędne x
@param y Współrzędne y
@param success Dane o powodzeniu strzału
@param timeinfo Czas wykonania strzełu
@param pNext Wskaźnik na kolejny element
*/
typedef struct Log {

	int x;
	int y;
	int success;
	struct tm* timeinfo;
	struct Log* pNext;
} Log;


/**
Struktura przechowuje statystyki gracza
@param name Nazwa gracza
@param unsolved Ilość statków przeciwnika które zostały do znalezienia
@param x Aktualna pozycja gracza w osi X
@param y Aktualna pozycja gracza w osi Y
@param tries Ilość prób odkrycia pola przeciwnika
@param moves Ilość ruchów po polu w ciągu całej gry
*/
typedef struct Stats {
	char name[16];
	int unsolved;
	int x, y;

	int tries; //zmiany
	long moves; //ruchy
	Log* pHead;
} Stats;


#endif