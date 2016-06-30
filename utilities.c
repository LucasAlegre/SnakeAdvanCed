#include "utilities.h"
#include <stdio.h>
#include <ctype.h>

///L� uma tecla do usu�rio, se for uma arrow key, transforma-a para WASD
char arrowKeysToWASD()
{
    char key;

    key = getch();    //ler o caracter posto pelo usu�rio
    key = toupper(key);

    if(key == -32)    //cod ascii das setas:
    {
        switch(getch())
        {
        case 72 :  //72 == seta para cima
            key = 'W';
            break;
        case 75 :  //75 == seta para esquerda
            key = 'A';
            break;
        case 80 :  //80 == seta para baixo
            key = 'S';
            break;
        case 77 :  //77 == tecla para direita
            key = 'D';
            break;
        }
    }

    return key;
}

///Apaga o cursor  MSDN: http://bit.ly/1UTxBYh
void hideCursor()
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    CONSOLE_CURSOR_INFO cci;
    cci.bVisible=FALSE;
    cci.dwSize=1; // dwSize deve ser entre 1 e 100.
    GetConsoleScreenBufferInfo(hStdOut, &csbi);
    SetConsoleCursorInfo(hStdOut,&cci);
}

///Fun��o para a colora��o do texto
void textcolor(int ForgC)
{
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }

    return;
}

///Define a posi��o do cursor no prompt
void gotoxy(int x, int y)
{
    static HANDLE h = NULL;
    if(!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(h,c);
}

///Define a posi��o do cursor no prompt para o t�tulo
void gotoTitle(int x, int y)
{
    gotoxy(x + HORIZONTAL_ADJUST_TITLE, y + VERTICAL_ADJUST_TITLE);
}

///Define a posi��o do cursor no prompt para outra parte do t�tulo
void gotoTITLE(int x, int y)
{
    static HANDLE h = NULL;
    if(!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x + HORIZONTAL_ADJUST_TITLE2, y + VERTICAL_ADJUST_TITLE};
    SetConsoleCursorPosition(h,c);
}

///Auxiliar para printar o menu
void gotoMenuXY(int x, int y)
{
    gotoxy(x + HORIZONTAL_ADJUST_MENU, y + VERTICAL_ADJUST_MENU);
}

///Define a posi��o do cursor dentro da matriz do mapa
void gotoMapXY(int x, int y)
{
    gotoxy(x + HORIZONTAL_ADJUST_MAP, y + VERTICAL_ADJUST_MAP);
}
