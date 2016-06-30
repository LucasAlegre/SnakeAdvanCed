#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#include "types.h"
#include "defines.h"

/// Printa o mapa
void printMap(int rows, int columns, char map[][COLUMNSMAX], int color);

///Printa apenas as pedras no mapa
void printRocks (int rows, int columns, int rocksNum, POSN rocks[], char map[][COLUMNSMAX]);

///Define as condições iniciais do jogo
void restartLevel(SNAKE *snake, int columns, int rows, POSN rats[], int speed, int *actualSpeed, POSN initialCoord, BOOL *eatenAllRats);

///Printa a snake dentro do mapa e faz consistência dos caracteres
void printSnake(SNAKE *snake);

///Lê um novo comando, fazendo consistência
char changeDirection(char direction);

///Lê string do teclado e aplica um cheat
void cheatCode(int *lifes, BOOL *endLevel, int *speed);

///Atualiza as coordenadas de cada parte do corpo e da cabeça
void updateSnakeCoord(SNAKE *snake);

///Printa informações do Nível
void printInfo(int level, int lifes, int score, int ratsEaten, int objetivo);

///Printa score no survival mode
void printScore(int score);

///Apaga o rastro da cobra
void eraseTrail(SNAKE snake);

///Analisa colisão da snake com bordas, com o próprio corpo e com as pedras, alterando score e o tamanho da snake
void checkColision(SNAKE *snake, BOOL *isDead, int rows, int columns, char map[][COLUMNSMAX], POSN rocks[], int rocksNum, int hasPassed[], int* score);

///Faz a snake aparecer do outro lado do mapa
void teleport(SNAKE *snake, int rows, int columns);

///Gera e printa os ratos na tela
void makeRats (int rows, int columns, POSN rats[], int ratNum, SNAKE *snake, char map[][COLUMNSMAX],int *color);

///Gera e printa a maçã na tela
void makeApple (int rows, int columns,POSN* apple, POSN rats[], int ratNum, SNAKE *snake, char map[][COLUMNSMAX]);

///Testa se a snake passou por um rato, alterando seu tamanho e o score
void eatRat(SNAKE *snake, POSN rats[], int* ratsEaten, int* score, int level);

///Testa se a snake passou por uma maçã
void eatApple(SNAKE *snake, POSN *apple, int *score, BOOL *endLevel);

///Executa uma fase do jogo
void playOneLevel(int level, int objetivo, int speed, LEVEL_SCENE scenario, int *lifes, int *score);

///Controla o modo story
void storyMode();

///Modo de jogo em que só há uma vida, e termina apenas quando o jogador morre
void survivalMode();

#endif // SNAKE_H_INCLUDED
