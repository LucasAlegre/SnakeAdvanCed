#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include "types.h"

///Printa Game Over na tela
void printGameOver();

///Printa na tela uma animação de texto
void ANIMATIONtext(char text[], int color);

///Dependendo do level, printa uma história diferente
void printHistoryLines(int level);

///Efeito de fade in
void fadeIN(int h, int w, int color, int option);

///Efeito de fade out
void fadeOUT(int h, int w, int color, int option);

///Coloca na tela um mapa 10x30 para os diálogos
void printLOBBYdeCONVERSA(int color);

///Coloca na tela a arte de cada nível
void print_lvlART(LEVEL_SCENE level, int plusx, int plusy);

#endif // ANIMATION_H_INCLUDED
