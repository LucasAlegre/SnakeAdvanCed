#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include "defines.h"

///Estrutura que guarda uma coordenada cartesiana
typedef struct str_posn
{
    int x;  //cordenada X
    int y;  //cordenada Y

} POSN;

///Estrutura para armazenar scores de cada jogador
typedef struct str_player
{
    char name[15];
    int score;

} PLAYER;

///Estrutura principal da snake
typedef struct str_snake
{
    int size;
    char direction;
    char body[ROWSMAX*COLUMNSMAX];
    int x[ROWSMAX*COLUMNSMAX];
    int y[ROWSMAX*COLUMNSMAX];

} SNAKE;

///Auxiliar para printar o título do menu
typedef struct str_level_scene
{
    int color;
    char art[10][20];

} LEVEL_SCENE;


#endif // TYPES_H_INCLUDED
