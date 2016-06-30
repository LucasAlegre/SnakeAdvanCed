/*
SNAKE AdvanCed

Lucas Nunes Alegre e Guilherme Gomes Haetinger
Cart�o 00274693 e 00274702
Turma D Algoritmos e Programa��o 2016/1 - Trabalho Final

*/

#include "defines.h"
#include "types.h"
#include "snake.h"
#include "files.h"
#include "animation.h"
#include "utilities.h"
#include "menu.h"

///Controle principal do jogo
int main()
{

    int op; //guarda o n�mero da op��o do menu

    hideCursor(); // Apaga o cursor de todo o jogo.

    do
    {
        op = menu(); //printa o menu e devolve um inteiro indicando a op��o selecionada no menu

        switch(op)
        {
        case 0:                //printa os highscores do modo story e survival
            printHighScores();
            break;
        case 2:              //joga o modo story
            storyMode();
            break;
        case 4:              //printa as instru��es
            printInstructions();
            break;
        case 6:              //joga o modo survival
            survivalMode();
            break;
        case 8:              //encerra o programa
            op = ESC;
            break;
        }

    }
    while(op != ESC);    //enquanto o programa n�o encerrou

    return 0;
}

