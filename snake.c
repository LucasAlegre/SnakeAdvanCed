#include "snake.h"
#include "animation.h"
#include "utilities.h"
#include "files.h"
#include <stdio.h>
#include <ctype.h>

/// Printa o mapa
void printMap(int rows, int columns, char map[][COLUMNSMAX], int color)
{
    textcolor(color);
    int i, j;

    for(i=0; i<rows; i++) //printa mapa com snake
    {
        for(j=0; j<columns; j++)
        {
            gotoMapXY(j,i);
            printf("%c", map[i][j]);
        }
    }
    printf("\n");
}

///Printa apenas as pedras no mapa
void printRocks (int rows, int columns, int rocksNum, POSN rocks[], char map[][COLUMNSMAX])
{
    textcolor(RED);
    int cont;

    for(cont=0; cont<rocksNum; cont++)  //vai para a coordenada de cada pedra e a imprime
    {
        gotoMapXY(rocks[cont].x, rocks[cont].y);
        printf("*");
    }
}

///Define as condições iniciais do jogo
void restartLevel(SNAKE *snake, int columns, int rows, POSN rats[], int speed, int *actualSpeed, POSN initialCoord, BOOL *eatenAllRats)
{
    int i;
    POSN outOfMap = {-2,-2}; //Coordenada fantasma fora do mapa para "guardar" ratos que não estão na tela

    for(i=0; i<4; i++)
    {
        rats[i] = outOfMap; //ratos inicializam fora do mapa
    }

    snake->size = 4;  // snake inicia com tamanho 4
    snake->direction = 'D';     //snake inicia virada para a direita

    *actualSpeed = speed;  //velocidade inicial

    snake->body[0] = '<';  //coloca caracteres iniciais do corpo
    snake->body[1] = 205;
    snake->body[2] = 205;
    snake->body[3] = 205;
    snake->body[4] = 205;

    for(i=0; i<rows*columns; i++)
    {
        snake->x[i] = outOfMap.x;  //zera todas as coordenadas da cobra antes de inicializar
        snake->y[i] = outOfMap.y;
    }

    snake->x[0] = initialCoord.x;    //preenche as coordenadas da snake de tamanho 4, deixando-a na horizontal
    snake->y[0] = initialCoord.y;
    snake->x[1] = initialCoord.x - 1;
    snake->y[1] = initialCoord.y;
    snake->x[2] = initialCoord.x - 2;
    snake->y[2] = initialCoord.y;
    snake->x[3] = initialCoord.x - 3;
    snake->y[3] = initialCoord.y;

    *eatenAllRats = 0;
}

///Printa a snake dentro do mapa e faz consistência dos caracteres
void printSnake(SNAKE *snake)
{
    textcolor(GREEN);
    int i;
    char headW = 'V', headA = '>', headS = '^', headD = '<', bodyV = 186, bodyH = 205, bodyDownRight = 188, bodyDownLeft = 200, bodyTopRight = 187, bodyTopLeft = 201;

    for(i = snake->size - 1; i >= 2; i--)  //cada parte do corpo recebe o caracter da parte anterior para a proxima repetiçao
        snake->body[i] = snake->body[i-1];

    for(i = snake->size - 1; i >= 0; i--)  //imprime toda a snake
    {
        gotoMapXY(snake->x[i], snake->y[i]);
        if(i==0) //caracteres da cabeça da cobra
        {
            switch(snake->direction)
            {
            case 'W':
                printf("%c", headW);
                snake->body[0] = headW;
                break;
            case 'A':
                printf("%c", headA);
                snake->body[0] = headA;
                break;
            case 'S':
                printf("%c", headS);
                snake->body[0] = headS;
                break;
            case 'D':
                printf("%c", headD);
                snake->body[0] = headD;
                break;
            }
        }
        else if(i==1) //caracteres da primeira parte do corpo após a cabeça
        {
            switch(snake->direction)  //dependendo da nova direção da snake e do caracter anterior da cabeça, atualiza e printa o caracter correspondente
            {
            case 'W':
                switch(snake->body[0])
                {
                case 'V':
                    printf("%c", bodyV);
                    snake->body[i] = bodyV;
                    break;
                case '>':
                    printf("%c", bodyDownLeft);
                    snake->body[i] = bodyDownLeft;
                    break;
                case '<':
                    printf("%c", bodyDownRight);
                    snake->body[i] = bodyDownRight;
                    break;
                }
                break;

            case 'A':
                switch(snake->body[0])
                {
                case '>':
                    printf("%c", bodyH);
                    snake->body[i] = bodyH;
                    break;
                case '^':
                    printf("%c", bodyDownRight);
                    snake->body[i] = bodyDownRight;
                    break;
                case 'V':
                    printf("%c", bodyTopRight);
                    snake->body[i] = bodyTopRight;
                    break;
                }
                break;

            case 'S':
                switch(snake->body[0])
                {
                case '^':
                    printf("%c", bodyV);
                    snake->body[i] = bodyV;
                    break;
                case '>':
                    printf("%c", bodyTopLeft);
                    snake->body[i] = bodyTopLeft;
                    break;
                case '<':
                    printf("%c", bodyTopRight);
                    snake->body[i] = bodyTopRight;
                    break;
                }
                break;

            case 'D':
                switch(snake->body[0])
                {
                case '<':
                    printf("%c", bodyH);
                    snake->body[i] = bodyH;
                    break;
                case '^':
                    printf("%c", bodyDownLeft);
                    snake->body[i] = bodyDownLeft;
                    break;
                case 'V':
                    printf("%c", bodyTopLeft);
                    snake->body[i] = bodyTopLeft;
                    break;
                }
                break;

            }
        }
        else printf("%c", snake->body[i]);
    }

}

/// Lê um novo comando, fazendo consistência
char changeDirection(char direction)
{
    char key;

    if(kbhit())   //lê apenas se uma tecla for apertada
    {
        key = getch(); //scaneia comando do usuario
        if(key == -32)          //cod ascii das setas:
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
        key = toupper(key);  //torna o caracter maisculo para teste

        if((key == 'W' && direction != 'S') || (key == 'S' && direction != 'W') || (key == 'P') || (key == 'C') ||
           (key == 'D' && direction != 'A') || (key == 'A' && direction != 'D') || (key == 'Q') || (key == ESC))
        {
            if(key==direction)
            {
                changeDirection(direction);
            }
            direction = key;  //troca comando apenas se o usuario teclou um comando válido
        }
    }
    return direction; //retorna a nova direção
}

///Lê uma string do teclado, se for uma das strings de cheat aplica o cheat
void cheatCode(int *lifes, BOOL *endLevel, int *speed)
{
    char cheatCode[20];
    gotoxy(5, 2);
    // viabiliza a entrada de uma cheat Code
    gets(cheatCode);
    if(strcmp(cheatCode, "katiau") == 0)  //torna o jogo rápido
    {
        *speed = 50;
    }
    if(strcmp(cheatCode, "banban") == 0)  //99 vidas
    {
        *lifes = 99;
    }
    else if(strcasecmp(cheatCode, "fofao") == 0)  //passa de fase
    {
        *endLevel = 1;
    }

}

///Atualiza as coordenadas de cada parte do corpo e da cabeça
void updateSnakeCoord(SNAKE *snake)
{
    int i;

    for(i = snake->size - 1; i > 0; i--)
    {
        snake->x[i] = snake->x[i-1];        //avança uma unidade pra todo corpo menos a cabeça
        snake->y[i] = snake->y[i-1];
    }

    switch(snake->direction)   //atualiza cabeça dependendo da tecla apertada
    {
    case 'W':
        (snake->y[0])--;
        break;
    case 'A':
        (snake->x[0])--;
        break;
    case 'S':
        (snake->y[0])++;
        break;
    case 'D':
        (snake->x[0])++;
        break;
    }
}

///Printa informações do Nível
void printInfo(int level, int lifes, int score, int ratsEaten, int objetivo)
{
    textcolor(GREEN);
    gotoxy(HORIZONTAL_ADJUST_INFO, VERTICAL_ADJUST_INFO);
    printf("Level: %d Lifes: %d Score: %04d Rats: %02d/%02d", level, lifes, score, ratsEaten, objetivo);
}

///Printa informações do Survival
void printScore(int score)
{
    textcolor(RED);
    gotoxy(HORIZONTAL_ADJUST_INFO, VERTICAL_ADJUST_INFO);
    printf("Score: %04d", score);
}

///Apaga o rastro da cobra
void eraseTrail(SNAKE snake)
{
    gotoMapXY(snake.x[snake.size - 1], snake.y[snake.size - 1]);
    printf(" ");
}

///Analisa colisão da snake com bordas, com o próprio corpo e com as pedras, alterando score e o tamanho da snake
void checkColision(SNAKE *snake, BOOL *isDead, int rows, int columns, char map[][COLUMNSMAX], POSN rocks[], int rocksNum, int hasPassed[], int* score)
{
    int cont, i;

    if(map[snake->y[0]][snake->x[0]] == '#') //testa colisão com a parede
    {
        Beep(400,100);
        *isDead=1;
    }

    if(map[snake->y[0]][snake->x[0]] == '*')  //testa colisão com as pedras
    {
        Beep(400,100);

        for(i = 0; i < rocksNum; i++)
        {
            if(hasPassed[i] == 0)
            {
                hasPassed[i] = 1;         //flag que a snake passou pela pedra
                i = rocksNum;
            }
        }

        eraseTrail(*snake);
        (snake->size)--;  //diminui o tamanho ao passar por uma pedra
        (*score)--;
    }

    for(i=0; i<rocksNum; i++)
    {
        if(hasPassed[i] == snake->size + 1)
        {
            printRocks(rows, columns, rocksNum, rocks, map);
            hasPassed[i] = 0;
        }
    }

    for(cont = 1; cont < snake->size; cont++)  //testa colisão com a própria snake
    {
        if(snake->x[cont] == snake->x[0] && snake->y[cont] == snake->y[0])
        {
            Beep(400, 100);
            *isDead = 1;
        }
    }

}

///Faz a snake aparecer do outro lado do mapa
void teleport(SNAKE *snake, int rows, int columns)
{
    if(snake->x[0] == 0)
    {
        gotoMapXY(snake->x[0], snake->y[0]);
        printf(" ");
        snake->x[0] = columns - 1;
    }
    else if(snake->x[0] == columns - 1)
    {
        gotoMapXY(snake->x[0], snake->y[0]);
        printf(" ");
        snake->x[0] = 0;
    }
    else if(snake->y[0] == 0)
    {
        gotoMapXY(snake->x[0], snake->y[0]);
        printf(" ");
        snake->y[0] = rows - 1;
    }
    else if(snake->y[0] == rows - 1)
    {
        gotoMapXY(snake->x[0], snake->y[0]);
        printf(" ");
        snake->y[0] = 0;
    }
}

///Gera e printa os ratos na tela
void makeRats (int rows, int columns, POSN rats[], int ratNum, SNAKE *snake, char map[][COLUMNSMAX],int *color)
{
    BOOL cond1, cond2, cond3, ok;
    int i;
    textcolor(*color);

    srand(time(NULL));  //semente de numeros aleatorios

    gotoMapXY(rats[ratNum].x, rats[ratNum].y);  //apaga o rato antigo
    printf(" ");

    rats[ratNum].x = 1 + (rand() % (columns-2));  //geração de coordenadas aleatorias
    rats[ratNum].y = 1 + (rand() % (rows-2));

    ok = 0;
    while(!ok)
    {
        cond1 = 0;  //inicializa as três condições necessarias para gerar um rato novo
        cond2 = 0;
        cond3 = 0;
        for(i = 0; i < snake->size; i++)  ///checa se nao gerou em cima da snake
        {
            if(rats[ratNum].x == snake->x[i] && rats[ratNum].y == snake->y[i])
            {
                cond1 = 1;
            }
        }

        for(i = 0; i < 4; i++)  /// checa se nao gerou em cima do rato
        {
            if(i != ratNum)
            {
                if(rats[i].x == rats[ratNum].x && rats[i].y == rats[ratNum].y)
                {
                    cond2 = 1;
                }
            }
        }

        if(map[rats[ratNum].y][rats[ratNum].x] == '#' || map[rats[ratNum].y][rats[ratNum].x] == '*') ///checa se nao gerou em pedra ou borda
        {
            cond3 = 1;
        }

        if(cond1 != 1 && cond2 != 1 && cond3 != 1)  //se as três condições forem verdadeiras, gera e imprime o rato
        {
            gotoMapXY(rats[ratNum].x, rats[ratNum].y);
            printf("&");
            ok = 1;
        }

        else  //gera uma nova tentativa de coordenada aleatoria
        {
            rats[ratNum].x = 1 + (rand() % (columns-2));
            rats[ratNum].y = 1 + (rand() % (rows-2));
            ok = 0;
        }
    }

    if(*color == 15) *color = 1;  //muda a cor do rato, não podendo ser a cor preta == 15
    else *color+=1;
}

///Gera e printa a maçã na tela
void makeApple (int rows, int columns,POSN* apple, POSN rats[], int ratNum, SNAKE *snake, char map[][COLUMNSMAX])
{
    BOOL cond1, cond2, cond3, ok;
    int i;

    textcolor(RED);

    srand(time(NULL));  //semente de numeros aleatorios

    apple->x = 1 + (rand() % (columns-2));  //geração de coordenadas aleatorias
    apple->y = 1 + (rand() % (rows-2));

    ok = 0;
    while(!ok)
    {
        cond1=0;  //inicializa as três condições necessarias para gerar um rato novo
        cond2=0;
        cond3=0;
        for(i=0; i<snake->size; i++)  ///checa se nao gerou em cima da snake
        {
            if(apple->x == snake->x[i] && apple->y == snake->y[i])
            {
                cond1 = 1;
            }
        }

        for(i=0; i<4; i++)  /// checa se nao gerou em cima do rato
        {
            if(rats[i].x == apple->x && rats[i].y == apple->y)
            {
                cond2 = 1;
            }
        }

        if(map[rats[ratNum].y][apple->x] == '#' || map[rats[ratNum].y][apple->x] == '*') ///checa se nao gerou em pedra ou borda
        {
            cond3 = 1;
        }

        if(cond1!= 1 && cond2 != 1 && cond3 !=1)  //se as três condições forem verdadeiras, gera e imprime o rato
        {
            gotoMapXY(apple->x, apple->y);
            printf("%c", APPLE);
            ok = 1;
        }

        else  //gera uma nova tentativa de coordenada aleatoria
        {
            apple->x = 1 + (rand() % (columns-2));  //geração de coordenadas aleatorias
            apple->y = 1 + (rand() % (rows-2));
            ok = 0;
        }

    }
}

///Testa se a snake passou por um rato, alterando seu tamanho e o score
void eatRat(SNAKE *snake, POSN rats[], int* ratsEaten, int* score, int level)
{
    int i;

    for(i=0; i<4; i++)
    {
        if(snake->y[0] == rats[i].y && snake->x[0] == rats[i].x)
        {
            Beep(1000, 100);
            (*score) += 1 * level;
            (snake->size)++;
            (*ratsEaten)++;
            rats[i].x = -2; //coordenadas fora do mapa
            rats[i].y = -2; //coordenadas fora do mapa
        }
    }

}

///Testa se a snake passou por uma maçã
void eatApple(SNAKE *snake, POSN *apple, int *score, BOOL *endLevel)
{
    if(snake->y[0] == apple->y && snake->x[0] == apple->x)
    {
        Beep(1000, 100);
        (*score) += 10;
        *endLevel = 1;  //passa de fase
    }
}

///Executa uma fase do jogo no modo story
void playOneLevel(int level, int objetivo, int speed, LEVEL_SCENE scenario, int *lifes, int *score)
{
    int rows, columns;  //Linhas e colunas do mapa
    int rocksNum;   // Número de pedras
    int ratsEaten;  //Número de ratos
    int ratNum;  //Indica qual o rato a ser gerado, há no máximo 4 ratos na tela
    int ratsColor; //Cor do rato a ser gerado
    int i;  // Usado nos loops for
    int cont; //Usado para contabilizar o número de movimentos da snake
    int actualSpeed; //velocidade que vai sendo aumentada
    char auxDirection;  //recebe direção antes de trocar a direção da snake
    BOOL isDead; //Flag de morte da snake
    BOOL levelEnded; //Flag que indica se o nível chegou ao fim
    BOOL eatenAllRats; //Flag que indica se todos os ratos necessário para gerar a maçã foram comidos

    char map[ROWSMAX][COLUMNSMAX];
    int hasPassed[ROWSMAX*COLUMNSMAX]; //array para indicar as pedras pelas quais a snake passou

    SNAKE snake;

    POSN initialCoord; //Coordenada onde a snake começa o nível

    POSN rocks[ROWSMAX*COLUMNSMAX];
    POSN rats[4];
    POSN apple = {500, 500}; //coordenada fora do mapa

    eatenAllRats = 0;
    ratsEaten = 0;
    ratNum = 0;
    ratsColor = GREEN; //primeiro rato é verde
    cont = 0;
    isDead = 0;
    levelEnded = 0;

    for(i=0; i<rocksNum; i++)
        hasPassed[i]=0;

    readMap(level, &rows, &columns, map, &rocksNum, rocks, &initialCoord);
    print_lvlART(scenario, columns + 5, 0);
    restartLevel(&snake, columns, rows, rats, speed, &actualSpeed, initialCoord, &eatenAllRats);
    fadeIN(rows, columns, GREY, 1);
    printMap(rows, columns, map, scenario.color);
    printRocks(rows, columns, rocksNum, rocks, map);
    printSnake(&snake);
    printInfo(level, *lifes, *score, ratsEaten, objetivo);
    getch(); //pausa o jogo

    while(*lifes > 0 && levelEnded == 0)
    {

        for(i=0; i<rocksNum; i++)
        {
            if(hasPassed[i] != 0)
               hasPassed[i] += 1;
        }

        print_lvlART(scenario, columns + 5, 0);
        printInfo(level, *lifes, *score, ratsEaten, objetivo);
        eraseTrail(snake);
        updateSnakeCoord(&snake);
        printSnake(&snake);
        checkColision(&snake, &isDead, rows, columns, map, rocks, rocksNum, hasPassed, score);
        teleport(&snake, rows, columns);

        if(*score < 0)
        {
            *score = 0;  //Não há score negativo!
        }

        cont++; //conta o número de movimentos
        if(cont % 10 == 0 && ratsEaten < objetivo) //a cada 10 movimentos gera um rato, se não for atingido o objetivo
        {
            makeRats(rows, columns, rats, ratNum, &snake, map, &ratsColor);
            ratNum++;
            if(ratNum == 4)
            {
                ratNum = 0;
            }
        }

        eatRat(&snake, rats, &ratsEaten, score, level);
        eatApple(&snake, &apple, score, &levelEnded);

        if(ratsEaten >= objetivo && eatenAllRats == 0) //gera maçã se forem comidos todos os ratos necessários
        {
            eatenAllRats = 1;
            makeApple(rows, columns, &apple, rats, ratNum, &snake, map);
        }

        if(isDead || snake.size == 1)  //Se a cobra teve uma colisão fatal ou perdeu todo o corpo exceto a cabeça
        {
            Beep(700, 100);
            isDead = 0;
            (*lifes)--;
            ratsEaten = 0; //Se morrer, deve comer todos os ratos de novo
            if(*lifes > 0) //Se ainda há vidas, continua o jogo
            {
                system("cls");
                print_lvlART(scenario, columns + 5, 0);
                restartLevel(&snake, columns, rows, rats, speed, &actualSpeed, initialCoord, &eatenAllRats);
                printMap(rows, columns, map, scenario.color);
                printRocks(rows, columns, rocksNum, rocks, map);
                printSnake(&snake);
                printInfo(level, *lifes, *score, ratsEaten, objetivo);
                getch(); //pausa o jogo
            }
        }

        Sleep(speed); //controla a velocidade do jogo
        if(speed > 100) //máxima velocidade do jogo
            speed -= 1;

        auxDirection = changeDirection(snake.direction); //lê nova direção to teclado
        if(auxDirection == 'P')
        {
            getch(); //Pausa o jogo
        }
        else if(auxDirection == 'C')
        {
            cheatCode(&(*lifes), &levelEnded, &speed); //Lê cheat code
        }
        else snake.direction = auxDirection;

        if(snake.direction == 'Q' || snake.direction == ESC) //Se o jogador aperta para sair, perde suas vidas para encerrar
        {
            *lifes = 0;
        }
    }

    fadeOUT(rows, columns, GREY, 1); //Efeito de fade out na tela
    system("cls");

}

///Controla o modo story
void storyMode()
{

    FILE *arq;
    int lifes;
    int score;
    int level;

    LEVEL_SCENE temple = {GREY,{176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,
                                176,176,176,176,176,176,176,178,178,178,178,178,178,176,176,176,176,176,176,176,
                                176,176,176,176,176,176,176,178,178,176,176,178,178,176,176,176,176,176,176,176,
                                176,176,176,176,176,176,176,178,178,176,176,178,178,176,176,176,176,176,176,176,
                                176,176,176,176,176,176,178,178,178,178,178,178,178,178,176,176,176,176,176,176,
                                176,176,176,176,176,178,178,178,178,178,178,178,178,178,178,176,176,176,176,176,
                                176,176,176,176,178,178,178,178,178,178,178,178,178,178,178,178,176,176,176,176,
                                176,176,176,178,178,178,178,178,178,178,178,178,178,178,178,178,178,176,176,176,
                                176,176,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,176,176,
                                176,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,176
                               }
                         };

    LEVEL_SCENE desert = {YELLOW,{176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,
                                  176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,
                                  176,176,176,176,176,176,176,176,176,176,176,178,178,176,176,176,176,176,176,176,
                                  176,176,176,176,176,176,176,176,176,176,178,178,178,178,176,176,176,176,176,176,
                                  176,176,176,176,176,176,176,176,176,178,178,178,178,178,178,176,176,176,176,176,
                                  176,176,178,178,178,176,176,176,178,178,178,178,178,178,178,178,176,176,176,176,
                                  176,178,178,178,178,178,176,177,177,178,178,178,178,178,178,178,178,176,176,176,
                                  178,178,178,178,178,178,178,178,177,177,177,178,178,178,178,178,178,178,176,176,
                                  178,178,178,178,178,178,178,178,178,177,177,177,178,178,178,178,178,178,178,176,
                                  178,178,178,178,178,178,178,178,178,178,178,177,178,178,178,178,178,178,178,178
                                 }
                         };

    LEVEL_SCENE forest = {GREEN,{176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,177,
                                 176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,177,
                                 176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,177,177,
                                 176,176,176,176,176,176,176,176,178,178,176,176,176,176,176,176,178,177,177,177,
                                 176,176,178,177,177,176,176,178,178,178,178,176,176,176,176,178,178,177,177,177,
                                 176,176,178,177,177,177,176,178,178,178,178,176,176,176,176,178,178,178,177,177,
                                 178,178,178,177,177,177,176,178,178,178,178,176,176,176,178,178,178,178,178,178,
                                 178,178,177,177,177,177,176,178,178,178,178,178,176,178,178,178,178,177,178,178,
                                 177,178,177,177,177,177,177,177,178,178,177,177,177,177,177,177,177,177,177,178,
                                 177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177
                                }
                         };

    LEVEL_SCENE sea = {LIGHT_BLUE, {176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,
                                    176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,
                                    176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,
                                    176,176,176,176,178,178,178,176,176,176,176,176,178,178,178,178,176,176,176,176,
                                    176,176,176,178,178,176,178,176,176,176,176,178,178,178,176,178,176,176,176,176,
                                    176,176,178,178,178,176,176,176,176,176,178,178,178,178,176,176,176,176,176,178,
                                    176,178,178,178,178,176,176,176,176,178,178,178,178,178,176,176,176,176,178,178,
                                    178,178,178,178,178,178,176,176,178,178,178,178,178,178,178,176,176,178,178,178,
                                    178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,
                                    178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178
                                   }
                      };

    system("mode con:cols=140 lines=40");

    level = 1;
    score = 0;
    lifes = 5;

    do
    {
        switch(level)
        {
        case 1:
            printLOBBYdeCONVERSA(GREY);
            print_lvlART(temple, 35, 0);
            printHistoryLines(1);
            playOneLevel(1, 5, 400, temple, &lifes, &score);
            break;

        case 2:
            playOneLevel(2, 10, 300, temple,  &lifes, &score);
            break;

        case 3:
            printLOBBYdeCONVERSA(GREY);
            gotoMapXY(25, 4);
            textcolor(13);
            printf("%c", 190);
            printHistoryLines(2);
            playOneLevel(3, 20, 250, temple, &lifes, &score);
            break;

        case 4:
            print_lvlART(temple, 35, 0);
            printLOBBYdeCONVERSA(GREY);
            gotoMapXY(25, 4);
            textcolor(PINK);
            printf("%c", 190); //printa personagem da história
            printHistoryLines(3);
            fadeOUT(10, 30, GREY, 1);
            printLOBBYdeCONVERSA(YELLOW);
            printHistoryLines(4);
            playOneLevel(4, 25, 200, desert, &lifes, &score);
            break;

        case 5:
            playOneLevel(5, 30, 200, desert, &lifes, &score);
            break;

        case 6:
            playOneLevel(6, 30, 150, desert, &lifes, &score);
            break;

        case 7:
            printHistoryLines(5);
            printLOBBYdeCONVERSA(GREEN);
            printHistoryLines(6);
            playOneLevel(7, 35, 150, forest, &lifes, &score);
            break;

        case 8:
            playOneLevel(8, 40, 150, forest, &lifes, &score);
            break;

        case 9:
            playOneLevel(9, 40, 100, forest, &lifes, &score);
            break;

        case 10:
            printHistoryLines(7);
            printLOBBYdeCONVERSA(LIGHT_BLUE);
            printHistoryLines(8);
            playOneLevel(10, 50, 100, sea, &lifes, &score);
            break;
        case 11:
            playOneLevel(11, 50, 100, sea, &lifes, &score);
            break;

        case 12:
            playOneLevel(12, 55, 90, sea, &lifes, &score);
            printHistoryLines(9);
            break;

        case 13:
            printHistoryLines(10);
            playOneLevel(13, 60, 80, temple, &lifes, &score);
            break;

        }

        if(lifes > 0)
        {
            level++; //passa de fase
            lifes++; //ganha uma vida
        }
        else if(lifes == 0)
        {
            printGameOver();
        }

    }
    while(lifes>0 && level <= 13);

    if(lifes > 0)
    {
        puts("\nYOU JUST WON THIS GAME, WOW!(You problably lost an expressive time of your life, or no)");
        puts("Now, check out these cheat codes:");
        puts("katiau\nbanban\nfofao");
        getch(); //pausa
        system("cls");
    }

    arq = fopen("highscore.bin", "rb+"); //Abre arquivo de highscore, informando caso de erro
    if(arq == NULL)
        printf("error");

    uptadeHighScore(score, arq); //Insere score no rank

}

///Modo de jogo em que só há uma vida, e termina apenas quando o jogador morre
void survivalMode()
{
    system("mode con:cols=90 lines=30"); //tamanho da tela de jogo

    LEVEL_SCENE hell   = {RED, {176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,177,
                                176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,177,
                                176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,177,177,
                                176,176,176,176,176,176,176,176,178,178,176,176,176,176,176,176,178,177,177,177,
                                176,176,178,177,177,176,176,178,178,178,178,176,176,176,176,178,178,177,177,177,
                                176,176,178,177,177,177,176,178,178,178,178,176,176,176,176,178,178,178,177,177,
                                178,178,178,177,177,177,176,178,178,178,178,176,176,176,178,178,178,178,178,178,
                                178,178,177,177,177,177,176,178,178,178,178,178,176,178,178,178,178,177,178,178,
                                177,178,177,177,177,177,177,177,178,178,177,177,177,177,177,177,177,177,177,178,
                                177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177
                               }
                         };  //cenário do modo de jogo

    FILE *arq;
    int score;  //pontuação
    int level;  //como só há um level nesse jogo, esta variavél serve apenas para o peso da pontuação
    int speed;  //velocidade do jogo
    int rows, columns;  //Linhas e colunas do mapa
    int rocksNum;   // Número de pedras
    int ratNum;  //Indica qual o rato a ser gerado, há no máximo 4 ratos na tela
    int ratsEaten;
    int ratsColor; //Cor do rato a ser gerado
    int i;  // Usado nos loops for
    int cont; //Usado para contabilizar o número de movimentos da snake
    char auxDirection; //
    BOOL isDead; //Flag de morte da snake

    char map[ROWSMAX][COLUMNSMAX];
    int hasPassed[ROWSMAX*COLUMNSMAX];

    SNAKE snake;

    POSN initialCoord; //Coordenada onde a snake começa o nível

    POSN rocks[ROWSMAX*COLUMNSMAX];
    POSN rats[4];

    ratNum = 0;
    ratsColor = 2;
    ratsEaten = 0;
    cont = 0;
    isDead = 0;
    level = 1;
    score = 0;
    speed = 200; //speed inicial

    for(i=0; i<rocksNum; i++)
        hasPassed[i]=0;

    readMap(42, &rows, &columns, map, &rocksNum, rocks, &initialCoord);
    restartLevel(&snake, columns, rows, rats, speed, &speed, initialCoord, &isDead);
    print_lvlART(hell, columns + 5, 0);
    fadeIN(rows, columns, GREY, 1);
    printMap(rows, columns, map, hell.color);
    printRocks(rows, columns, rocksNum, rocks, map);
    printSnake(&snake);
    getch(); //pausa o jogo

    while(!isDead)
    {

        for(i=0; i<rocksNum; i++)
        {
            if(hasPassed[i]!=0) hasPassed[i]+=1;
        }

        print_lvlART(hell, columns + 5, 0);
        printScore(score);
        eraseTrail(snake);
        updateSnakeCoord(&snake);
        printSnake(&snake);
        checkColision(&snake, &isDead, rows, columns, map, rocks, rocksNum, hasPassed, &score);

        if(score < 0)
        {
            score = 0;  //Não há score negativo!
        }

        cont++; //contador de movimentos
        if(cont % 10 == 0)
        {
            makeRats(rows, columns, rats, ratNum, &snake, map, &ratsColor); //gera e printa um rato
            ratNum++;
            if(ratNum == 4)  //Há 4 ratos, de 0 a 3, logo rato 4 == rato 0
            {
                ratNum = 0;
            }
        }

        eatRat(&snake, rats, &ratsEaten, &score, level); //checa se um rato foi comido

        Sleep(speed); //controla a velocidade do jogo
        if(speed > 100) //máxima velocidade do jogo
            speed -= 1;

        auxDirection = changeDirection(snake.direction); //lê nova direção to teclado
        if(auxDirection == 'P')
        {
            getch(); //Pausa o jogo
        }
        else if(auxDirection == 'C')
        {
            cheatCode(&isDead, &isDead, &speed); //Lê cheat code
        }
        else if(auxDirection == 'Q' || auxDirection == ESC) //Se o jogador aperta para sair, perde suas vidas para encerrar
        {
            isDead = 1;
        }
        else snake.direction = auxDirection; //só troca a direção se a nova direção não for uma tecla de pause ou saída

    }

    fadeOUT(rows, columns, GREY, 1); //Efeito de fade out na tela
    printGameOver();

    arq = fopen("highscore_survival.bin", "rb+"); //Abre arquivo de highscore, informando caso de erro
    if(arq == NULL)
        printf("error");

    uptadeHighScore(score, arq); //coloca o score no rank

    system("cls");

}

