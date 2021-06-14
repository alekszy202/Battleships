#ifndef DEFINES
#define DEFINES

#include <stdlib.h>
#include <Windows.h>

//keys
#define NEW_LINE			10
#define ENTER				13
#define ESC					27
#define ARROW				224
#define UP					72
#define DOWN				80
#define LEFT				75
#define RIGHT				77

//game
#define MIN_SHIPS			5
#define MAX_SHIPS			20
#define ROWS				10
#define COLUMNS				10
#define SHIP				1
#define WATER				0
#define GAMEOVER			1
#define GAMERUNS			0

//board
#define CORNER_UL			(char)201
#define CORNER_UR			(char)187
#define	CORNER_BL			(char)200
#define CORNER_BR			(char)188

#define CROSS				(char)197
#define SQUARE				(char)254

#define VERTICAL_SINGLE		(char)196
#define VERTICAL_DOUBLE		(char)186
#define HORIZANTAL_SINGLE	(char)179
#define HORIZONTAL_DOUBLE	(char)205

//colors
#define HANDLE_CONSOLE		GetStdHandle(STD_OUTPUT_HANDLE)
#define	BLACK_ON_WHITE		240
#define	WHITE_ON_BLACK		15
#define	RED_ON_BLACK		12
#define	GREEN_ON_BLACK		10

//file errors
#define NOT_EXIST				-1
#define BAD_FORMAT				0
#define FILE_FINE				1
#define NUMBER_OF_SHIPS_ERROR	2

#endif