#ifndef PROGRAM_MANAGMENT
#define PROGRAM_MANAGMENT

#include <stdlib.h>
#include <Windows.h>

/**
Obsługa wszystkich funkcji, zmiennych i struktur zarządzających grą
@param argc Liczba przełączników podanych przy włączeniu programu
@param argv[] Przełączniki podane przy włączaniu programu
*/
void PlayMode(int argc, char* argv[]);

/**
Obsługa trybu generowania pustych tablic do zapełnienia przed graczy
@param argc Liczba przełączników podanych przy włączeniu programu
@param argv[] Przełączniki podane przy włączaniu programu
*/
void EmptyMode(int argc, char* argv[]);

/**
Tryb pseudolosujący plansze do gry o podanych przez graczy parametrach
@param argc Liczba przełączników podanych przy włączeniu programu
@param argv[] Przełączniki podane przy włączaniu programu
*/
void BuildMode(int argc, char* argv[]);

#endif