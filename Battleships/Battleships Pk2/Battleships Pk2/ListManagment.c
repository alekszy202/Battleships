#include <stdio.h>
#include <time.h>
#include <windows.h>
#include "Defines.h"
#include "Structures.h"
#include "GameManagment.h"
#include "IOManagment.h"
#include "ListManagment.h"

/**
Dodaje element do listy Logów przechowujących informacje o wykonanych przez gracza strzałach
@param pHead Głowa listy
@param x Współrzędne X
@param y Współrzędne Y
@param success Informacje o powodzeniu strzału
*/
void addLog(Log** pHead, int x, int y, int success)
{
	if (*pHead == NULL)
	{
		struct Log *newLog = (Log*)malloc(sizeof(Log));
		newLog->x = x;
		newLog->y = y;
		newLog->success = success;

		time_t rawtime;
		time(&rawtime);
		newLog->timeinfo = localtime(&rawtime);

		newLog->pNext = NULL;

		*pHead = newLog;
	}
	else
	{
		Log* tmp = *pHead;

		while (tmp->pNext)
			tmp = tmp->pNext;

		tmp->pNext = (Log*)malloc(sizeof(Log));

		tmp->pNext->x = x;
		tmp->pNext->y = y;
		tmp->pNext->success = success;
		
		time_t rawtime;
		time(&rawtime);
		tmp->pNext->timeinfo = localtime(&rawtime);

		tmp->pNext->pNext = NULL;
	}
}


/**
Funkcja usuwa dynamicznie zaalokowaną listę Logów
@param pHead Głowa listy
*/
void deleteLog(Log** pHead)
{
	while (*pHead)
	{
		Log* tmp = (*pHead)->pNext;
		free(*pHead);
		*pHead = tmp;
	}
	free(*pHead);
	*pHead = NULL;
}