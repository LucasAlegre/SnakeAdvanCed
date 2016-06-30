#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED

#include "defines.h"
#include "types.h"

///Lê uma tecla do usuário, se for uma arrow key, transforma-a para WASD
char arrowKeysToWASD();

///Apaga o cursor  MSDN: http://bit.ly/1UTxBYh
void hideCursor();

///Função para a coloração do texto
void textcolor(int ForgC);

///Define a posição do cursor no prompt
void gotoxy(int x, int y);

///Define a posição do cursor no prompt para o título
void gotoTitle(int x, int y);

///Define a posição do cursor no prompt para outra parte do título
void gotoTITLE(int x, int y);

///Define a posição do cursor no prompt para o menu
void gotoMenuXY(int x, int y);

///Define a posição do cursor dentro da matriz do mapa
void gotoMapXY(int x, int y);

#endif // UTILITIES_H_INCLUDED
