#ifndef DEFINES_H_INCLUDED
#define DEFINES_H_INCLUDED

///Bibliotecas:
#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <time.h>

///Maxímo do mapa
#define ROWSMAX 200
#define COLUMNSMAX 200

///Ajuste necessário para as funções de gotoxy
#define HORIZONTAL_ADJUST_INFO 5
#define VERTICAL_ADJUST_INFO 1
#define VERTICAL_ADJUST_TITLE 1
#define HORIZONTAL_ADJUST_TITLE 2
#define HORIZONTAL_ADJUST_TITLE2 20
#define VERTICAL_ADJUST_MENU 1
#define HORIZONTAL_ADJUST_MENU 45
#define VERTICAL_ADJUST_MAP 3
#define HORIZONTAL_ADJUST_MAP 5

///ASCII
#define ESC 27             ///Código ascii da tecla ESC
#define ENTER 13           ///Código ascii da tecla Enter
#define APPLE 208          //Ascii caracter da maçã

///Referência das cores:
#define YELLOW 6
#define WHITE 15
#define RED 4
#define LIGHT_RED 12
#define CIANO 3
#define LIGHT_GREEN 10
#define GREEN 2
#define GREEN2 18
#define GREY 8
#define BLUE 1
#define LIGHT_BLUE 11
#define BLUE2 9
#define BROWN 42
#define PINK 13

#endif // DEFINES_H_INCLUDED
