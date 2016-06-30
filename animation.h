#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include "types.h"

///Printa Game Over na tela
void printGameOver();

///Printa na tela uma anima��o de texto
void ANIMATIONtext(char text[], int color);

///Dependendo do level, printa uma hist�ria diferente
void printHistoryLines(int level);

///Efeito de fade in
void fadeIN(int h, int w, int color, int option);

///Efeito de fade out
void fadeOUT(int h, int w, int color, int option);

///Coloca na tela um mapa 10x30 para os di�logos
void printLOBBYdeCONVERSA(int color);

///Coloca na tela a arte de cada n�vel
void print_lvlART(LEVEL_SCENE level, int plusx, int plusy);

#endif // ANIMATION_H_INCLUDED
