#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED

#include "defines.h"
#include "types.h"

///L� uma tecla do usu�rio, se for uma arrow key, transforma-a para WASD
char arrowKeysToWASD();

///Apaga o cursor  MSDN: http://bit.ly/1UTxBYh
void hideCursor();

///Fun��o para a colora��o do texto
void textcolor(int ForgC);

///Define a posi��o do cursor no prompt
void gotoxy(int x, int y);

///Define a posi��o do cursor no prompt para o t�tulo
void gotoTitle(int x, int y);

///Define a posi��o do cursor no prompt para outra parte do t�tulo
void gotoTITLE(int x, int y);

///Define a posi��o do cursor no prompt para o menu
void gotoMenuXY(int x, int y);

///Define a posi��o do cursor dentro da matriz do mapa
void gotoMapXY(int x, int y);

#endif // UTILITIES_H_INCLUDED
