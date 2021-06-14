#ifndef LISTMANAGMENT
#define LISTMANAGMENT

/**
Dodaje element do listy Logów przechowujących informacje o wykonanych przez gracza strzałach
@param pHead Głowa listy
@param x Współrzędne X
@param y Współrzędne Y
@param success Informacje o powodzeniu strzału
*/
void addLog(Log** pHead, int x, int y, int success);


/**
Funkcja usuwa dynamicznie zaalokowaną listę Logów
@param pHead Głowa listy
*/
void deleteLog(Log** pHead);

#endif