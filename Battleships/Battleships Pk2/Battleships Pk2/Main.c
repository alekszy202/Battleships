#include <stdio.h>
#include "Defines.h"
#include "ProgramManagment.h"

int main(int argc, char* argv[]) 
{
	srand(time(0));
	if (argc > 1 && argc < 7) 
	{
		//<PLAY> Gra w statki
		if (strcmp(argv[1], "-p") == 0) 
		{
			if (argc == 6)
			{
				if (strstr(argv[3], ".txt") && (strstr(argv[5], ".txt")))
				{
					if ((strcmp(argv[2], "-p1") == 0) && (strcmp(argv[4], "-p2") == 0)) 
					{
							PlayMode(argc, argv); //Wywołanie gry
					}
					else printf("Podano nieprawidlowe przelaczniki!\n");
				}
				else printf("Nazwa pliku wejsciowego nie posiada rozszerzenia .txt!\n");
			}
			else printf("Uzycie trybu PLAY wymaga szesciu przelacznikow!\n");
		}

		//<EMPTY> Generowanie pustej planszy
		else if (strcmp(argv[1], "-e") == 0) 
		{
			if (argc == 2)
			{
				EmptyMode(argc, argv);	//Wywołanie generowania
				printf("Puste pliki szablonu gry zostaly wygenerowane pod nazwa p1.txt oraz p2.txt\n");
			}
			 else printf("Uzycie trybu EMPTY wymaga jednego przelacznika!\n");
		}

		//<BUILD> Generowanie planszy o losowych wartosciach
		else if (strcmp(argv[1], "-b") == 0) 
		{
			if(argc == 4)
			{
				if (strstr(argv[2], ".txt"))
				{
					BuildMode(argc, argv); //Wywołanie generowania
				}
				else printf("Nazwa pliku wejsciowego nie posiada rozszerzenia .txt!\n");
			}
			else printf("Uzycie trybu BUILD wymaga trzech przelacznikow!\n");
		}
		else printf("Niepoprawny przelacznik poczatkowy!\n");
	}
	else printf("Zla ilosc przelacznikow!\n");

	system("Pause");
	return 0;
}